package geniusweb.sampleagent;

import geniusweb.issuevalue.Bid;
import geniusweb.issuevalue.Domain;
import geniusweb.issuevalue.Value;
import geniusweb.profile.PartialOrdering;

import java.util.HashMap;
import java.util.Set;

public class OpponentModel {
    PartialOrdering profile; // profile of the agent
    Domain domain; // domain of the agent
    Set<String> issues; // the set of the issues in hand
    HashMap<String,HashMap<Value, Integer>> frequencies; // data structure for holding the frequencies
    int bidCount; // number of bids used for frequency count
    public OpponentModel(PartialOrdering profile) {
        this.profile = profile;
        this.domain = profile.getDomain();
        this.issues = domain.getIssues();
        this.bidCount = 0;
        this.frequencies = new HashMap<>();
        for(String issue : this.issues) {
            HashMap<Value,Integer> tmp = new HashMap<>();
            for (Value value : domain.getValues(issue)) {
                tmp.put(value,0);
            }
            frequencies.put(issue, tmp);
        }
    }


    /**
     * The function updates the frequencies structure using the given bid.
     * @param bid update the frequency of issue-value pair using given bid
     */
    public void updateFrequency(Bid bid){
        for(String issue : bid.getIssues()){
            HashMap<Value,Integer> tmp = frequencies.get(issue);
            Value value = bid.getValue(issue);
            int oldFreq = tmp.get(value);
            tmp.put(value,oldFreq+1);
            frequencies.put(issue,tmp);
        }
        this.bidCount++;
    }

    /**
     * The function returns the frequency of the issue-value pair given.
     * @param issue the issue of the value asked for
     * @param value the value asked for
     * @return frequency of issue-value pair
     */
    private int getFrequency(String issue,Value value){
        return frequencies.get(issue).get(value);
    }

    /**
     * @return total frequency of all values
     */
    private int getTotalFrequency(){
        int sum = 0;
        for(HashMap<Value,Integer> hashMap : frequencies.values()){
            for(Integer integer : hashMap.values()){
                sum += integer;
            }
        }
        return sum;
    }

    /**
     * @param bid the bid to get the importance of
     * @param knownSpace the number of bids in the knownSpace
     * @param totalSpace the number of bids in the AllBidsList
     * @return the importance ratio of the given bid.
     */
    public double getImportance(Bid bid,double knownSpace,double totalSpace){
        if( bidCount == 0)
           return 1.0;
        double totalBidFrequency = 0;
        for(String issue : bid.getIssues()){
            totalBidFrequency += getFrequency(issue,bid.getValue(issue));
        }
        return (totalBidFrequency / getTotalFrequency())*( 1 - (knownSpace/totalSpace))  + (totalBidFrequency / getTotalFrequency());
    }


}
