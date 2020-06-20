package geniusweb.sampleagent;

import geniusweb.issuevalue.Bid;
import geniusweb.issuevalue.Domain;
import geniusweb.profile.DefaultPartialOrdering;
import geniusweb.profile.Profile;
import geniusweb.profile.utilityspace.UtilitySpace;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.*;

/**
 * A simple list of bids, but all bids are fully ordered (better or worse than
 * other bids in the list).
 */
public class SimpleLinearOrdering implements UtilitySpace {

    public Domain domain;
    public List<Bid> bids; // worst bid first, best bid last.
    public Profile profile;

    SimpleLinearOrdering(Profile profile) {
        this(profile.getDomain(), getSortedBids(profile));
        this.profile = profile;
    }
    /**
     * @param domain
     * @param bids   a list of bids, ordered from lowest to highest util. The
     *               first bid will have utility 0, the last utility 1. If only
     *               0 or 1 bid in the list, or if the bid is not known, it will
     *               have utility 0.
     */
    SimpleLinearOrdering(Domain domain, List<Bid> bids) {
        this.domain = domain;
        this.bids = bids;
    }

    /**
     * @param profile
     * @return a list of bids in the profile sorted from low to high utility.
     */
    private static List<Bid> getSortedBids(Profile profile) {
        if (!(profile instanceof DefaultPartialOrdering)) {
            throw new UnsupportedOperationException(
                    "Only DefaultPartialOrdering supported");
        }
        DefaultPartialOrdering prof = (DefaultPartialOrdering) profile;
        List<Bid> bidslist = prof.getBids();
        // NOTE sort defaults to ascending order, this is missing in docs.
        Collections.sort(bidslist, new Comparator<Bid>() {

            @Override
            public int compare(Bid b1, Bid b2) {
                return prof.isPreferredOrEqual(b1, b2) ? 1 : -1;
            }

        });

        return bidslist;
    }

    public List<Bid> getSortedBids(Bid receivedBid){
        if(!bids.contains(receivedBid)) {
            ArrayList<Bid> currentSortedBids = (ArrayList<Bid>) getSortedBids(this.profile);
            currentSortedBids.add(currentSortedBids.size(),receivedBid);
            DefaultPartialOrdering dpo = (DefaultPartialOrdering) profile;
            Collections.sort(currentSortedBids, (o1, o2) -> dpo.isPreferredOrEqual(o1, o2) ? 1 : -1);

            this.bids = currentSortedBids;
            int i = currentSortedBids.indexOf(receivedBid);
            return currentSortedBids;
        }
        return this.bids;
    }
    public SimpleLinearOrdering copy(){
        SimpleLinearOrdering tmp = new SimpleLinearOrdering(this.profile);
        tmp.bids = this.bids;
        tmp.domain = this.domain;
        return tmp;
    }
    @Override
    public String getName() {
        throw new UnsupportedOperationException();
    }

    @Override
    public Domain getDomain() {
        return domain;
    }

    @Override
    public Bid getReservationBid() {
        throw new UnsupportedOperationException();
    }

    @Override
    public BigDecimal getUtility(Bid bid) {
        if (bids.size() < 2 || !bids.contains(bid)) {
            return BigDecimal.ZERO;
        }
        // using 8 decimals, we have to pick something here
        return new BigDecimal(bids.indexOf(bid)).divide(new BigDecimal((bids.size() - 1)), 8, RoundingMode.HALF_UP);
    }

    /**
     * @param bid
     * @return true iff bid is contained in this ordering
     */
    public boolean contains(Bid bid) {
        return bids.contains(bid);
    }

    /**
     * @return list of all bids in the current ordering.
     */
    public List<Bid> getBids() {
        return Collections.unmodifiableList(bids);
    }

    /**
     * @param bid       a new bid to be inserted
     * @param worseBids all bids that are worse than this bid.
     * @return a SimpleLinearOrdering, updated with the given comparison. Thee
     * bid will be inserted after the first bid that is not worse than
     * bid.
     */
    public SimpleLinearOrdering with(Bid bid, List<Bid> worseBids) {
        int n = 0;
        while (n < bids.size() && worseBids.contains(bids.get(n))) {
            n++;
        }
        LinkedList<Bid> newbids = new LinkedList<Bid>(bids);
        newbids.add(n, bid);

        return new SimpleLinearOrdering(domain, newbids);
    }
}
