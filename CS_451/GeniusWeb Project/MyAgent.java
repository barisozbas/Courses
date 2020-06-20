package geniusweb.sampleagent;

import geniusweb.actions.*;
import geniusweb.bidspace.AllBidsList;
import geniusweb.issuevalue.Bid;
import geniusweb.party.Capabilities;
import geniusweb.party.DefaultParty;
import geniusweb.party.inform.*;
import geniusweb.profile.PartialOrdering;
import geniusweb.profileconnection.ProfileConnectionFactory;
import geniusweb.profileconnection.ProfileInterface;
import geniusweb.progress.Progress;
import geniusweb.progress.ProgressRounds;
import tudelft.utilities.logging.Reporter;

import java.io.IOException;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.time.Duration;
import java.time.LocalDateTime;
import java.util.*;
import java.util.logging.Level;

/**
 * A simple implementation of a SHAOP party that can handle only bilateral
 * negotiations (1 other party). It will ignore all other parties except the one
 * that has the turn right before us. It estimates the utilities of bids by
 * assigning a linear increasing utility from the orderings that have been
 * created.
 * <p>
 * <b>Requirement<b> the initial {@link PartialOrdering} must contain at least
 * the bids with lowest utility and highest utility, and the proper comparison
 * info for these two bids.
 */


public class MyAgent extends DefaultParty {

    private BigDecimal lowBoundaryOffer = new BigDecimal("0.5"); // decimal value that sets the limit for the lowest utility for the bid to offer
    private BigDecimal lowBoundaryAccept = new BigDecimal("0.85"); // decimal value for the lowest utility of the bid to accept.
    private BigDecimal lowBoundaryOpponentOffer = new BigDecimal("0.50"); // decimal value that sets the limit for the lowest importance for the opponent of the bid to offer
    protected ProfileInterface profileint;
    protected PartialOrdering partialprofile;
    private Bid lastReceivedBid = null;
    private PartyId me;
    private Progress progress;
    private AllBidsList allbids;
    private List<Bid> orderedBids;
    private SimpleLinearOrdering orderedBidSLO; // Hold the known bid space in orderly fashion
    private Action lastReceivedAction = null;
    private Bid lastOfferedBid;
    private List<Bid> allBidsCopy;
    private OpponentModel opponentModel; // opponent model class
    private LocalDateTime elicitStartTime; // global variable to hold elicitComparison start time.
    private final int elicitTimeout = 3; // how many seconds should the elicit comparison can run for.

    public MyAgent() {
        super();
    }

    public MyAgent(Reporter reporter) {
        super(reporter); // for debugging
    }

    @Override
    public void notifyChange(Inform info) {
        try {
            if (info instanceof Settings) {
                Settings settings = (Settings) info;
                this.profileint = ProfileConnectionFactory.create(settings.getProfile().getURI(), getReporter());
                this.me = settings.getID();
                this.progress = settings.getProgress();
                partialprofile = (PartialOrdering) profileint.getProfile();
                allbids = new AllBidsList(partialprofile.getDomain());
                allBidsCopy = AllBidsListToList(allbids);
                orderedBidSLO = new SimpleLinearOrdering(profileint.getProfile());
                orderedBids = orderedBidSLO.getBids();
                opponentModel = new OpponentModel(partialprofile);

            } else if (info instanceof ActionDone) {
                lastReceivedAction = ((ActionDone) info).getAction();
                if (lastReceivedAction instanceof Offer) {
                    lastReceivedBid = ((Offer) lastReceivedAction).getBid();
                } else if (lastReceivedAction instanceof Comparison) {
                    if (elicitStartTime == null)
                        elicitStartTime = LocalDateTime.now();
                    orderedBidSLO = orderedBidSLO.with(((Comparison) lastReceivedAction).getBid(), ((Comparison) lastReceivedAction).getWorse());
                    myTurn();
                }
            } else if (info instanceof YourTurn) {
                myTurn();
            } else if (info instanceof Finished) {
                getReporter().log(Level.INFO, "Final outcome:" + info);
            }
        } catch (Exception e) {
            throw new RuntimeException("Failed to handle info", e);
        }
    }

    @Override
    public Capabilities getCapabilities() {
        return new Capabilities(new HashSet<>(Arrays.asList("SHAOP")));
    }

    @Override
    public String getDescription() {
        return "Communicates with COB party to figure out which bids are good. Accepts bids with utility > 0.9. Offers random bids. Requires partial profile";
    }

    /**
     * Called when it's (still that is elicitComparison) our turn and we should take some action. Also
     * Updates the progress if necessary.
     */
    private void myTurn() throws IOException {
        allBidsCopy = AllBidsListToList(allbids); // used for elicitComparison requests
        Action action = null; // action to send filled later down in the method

        //if starting new send highest utility bid
        if (this.lastReceivedBid == null) {
            Bid bidToOffer = orderedBids.get(orderedBids.size() - 1);
            lastOfferedBid = bidToOffer;
            action = new Offer(me, bidToOffer);
        } else {
            // try to get the utility of received bid
            if (!orderedBidSLO.contains(lastReceivedBid) && !(lastReceivedAction instanceof Comparison)) {
                action = new ElicitComparison(me, lastReceivedBid, orderedBidSLO.getBids());
                getConnection().send(action);
                return;
            }
            //put lastreceivedbid into known bid space and reorder
            orderedBidSLO.getSortedBids(lastReceivedBid);
            //update opponent model with the received bid.
            opponentModel.updateFrequency(lastReceivedBid);

            // if the received bid is acceptable then accept it
            if (isGood(lastReceivedBid)) {
                System.out.println("ACCEPTING " + lastReceivedBid);
                action = new Accept(me, lastReceivedBid);
            } else {
                // if it is not good, try to find a bid to offer

                // check the time for elicitTimeout
                    LocalDateTime current = LocalDateTime.now();
                    if(elicitStartTime == null)
                        elicitStartTime = LocalDateTime.now();
                    Duration duration = Duration.between(elicitStartTime, current);

                    // if the time is up, find a bid using the known space
                    if (duration.getSeconds() >= elicitTimeout) {
                        for (Bid bid : orderedBidSLO.getBids()) {
                            //check if the bid's utility is higher than lastreceivedbid which is not accepted.
                            if (orderedBidSLO.getUtility(bid).doubleValue() > orderedBidSLO.getUtility(lastReceivedBid).doubleValue()) {
                                // now check if the bid is the same as the last offered and if not check if it passes the threshold.
                                if ((!bid.equals(lastOfferedBid)) && orderedBidSLO.getUtility(bid).compareTo(lowBoundaryOffer) >= 0) {
                                    action = new Offer(me, bid);
                                    lastOfferedBid = bid;
                                }
                            }
                        }
                        //since we found a bid we can reset the time
                        elicitStartTime = null;
                    }
                else {
                    // if the time is not up find a bid from AllBidsList with ElicitComparison or orderedBidSLO
                    while (allBidsCopy.size() > 0) {
                        Collections.shuffle(allBidsCopy); // shuffle for eliminating duplication issue
                        Bid tmp = allBidsCopy.get(0);
                        allBidsCopy.remove(0);
                        // if the bid is in the knownspace then there is no need for ElicitComparison
                        if (orderedBidSLO.getBids().contains(tmp)) {
                            //check if the bid's utility is higher than the last received bid
                            if (orderedBidSLO.getUtility(tmp).doubleValue() > orderedBidSLO.getUtility(lastReceivedBid).doubleValue()) {
                                // check if the bid is not the same as the last offered bid and check if it passes the utility threshold
                                if ((!tmp.equals(lastOfferedBid)) && orderedBidSLO.getUtility(tmp).compareTo(lowBoundaryOffer) >= 0) {
                                    //check if the bid passes the importance for the opponent
                                    if (opponentModel.getImportance(tmp, orderedBidSLO.bids.size(), allbids.size().doubleValue()) >= lowBoundaryOpponentOffer.doubleValue()) {
                                        action = new Offer(me, tmp);
                                        lastOfferedBid = tmp;
                                        break;
                                    }
                                }
                            }
                        } else {
                            action = new ElicitComparison(me, tmp, orderedBidSLO.getBids());
                            getConnection().send(action);
                            return;
                        }
                    }
                }
            }


        }
        // if we could not find a bid send the highest utility bid
        if (action == null) {
            Bid bidToOffer = orderedBids.get(orderedBids.size() - 1);
            action = new Offer(me, bidToOffer);
            lastOfferedBid = bidToOffer;
        }
        getConnection().send(action);

        // progress the round
        if (progress instanceof ProgressRounds) {
            progress = ((ProgressRounds) progress).advance();
        }
    }


    /**
     * The method checks if the bid given should be
     * accepted or not.
     * @param bid bid to check for acceptance
     * @return true for good, false for not good
     */
    private boolean isGood(Bid bid) {
        if (bid == null) {
            return false;
        }
        // check the utility and normalize it by the size of the known space to get a more approximate result of the true utility.
        return orderedBidSLO.getUtility(bid).doubleValue()* (orderedBidSLO.getBids().size()/allbids.size().doubleValue()) >= lowBoundaryAccept.doubleValue();
    }

    // make a copy of AllBidsList in List form
    private List<Bid> AllBidsListToList(AllBidsList abl) {
        ArrayList<Bid> tmp = new ArrayList<>();
        for (Bid bid : abl)
            tmp.add(bid);
        return tmp;
    }

}
