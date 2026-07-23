package edu.pdx.cs.joy.dahuynh;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class PhoneBill implements Serializable
{    //Data Variables
    private final String customer;
    private final List<PhoneCall> phoneCalls;

    //Constructor
    public PhoneBill(String customer) {
        this.customer = customer;
        this.phoneCalls = new ArrayList<PhoneCall>(); // Initialize with ArrayList
    }
    public String getCustomer() {
        return this.customer;
    }
    public List<PhoneCall> getCalls(){return this.phoneCalls;}

    public void addCall(PhoneCall newCall){
        phoneCalls.add(newCall);
    }
}

