package edu.pdx.cs.joy.dahuynh;

import edu.pdx.cs.joy.AbstractPhoneBill;

import java.io.*;
import java.time.Duration;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;


public class PhoneBill extends AbstractPhoneBill<PhoneCall> {
  //Data Variables
  private final String customer;
  private List<PhoneCall> phoneCalls;

  //Constructor
  public PhoneBill(String customer) {
    this.customer = customer;
    this.phoneCalls = new ArrayList<PhoneCall>(); // Initialize with ArrayList
  }


  //Customer getter
  @Override
  public String getCustomer() {
    return this.customer;
  }

  //Adds phone call objects into phone bill
  @Override
  public void addPhoneCall(PhoneCall call) {
    phoneCalls.add(call);

  }


  public void sortPhoneCalls() {
    Collections.sort(phoneCalls);
  }

  @Override
  public Collection<PhoneCall> getPhoneCalls() {
    return this.phoneCalls;
  }


  public boolean printPhone(){
    if(this.phoneCalls == null){
      return false;
    }
    System.out.println("\nCustomer: " + this.getCustomer() + "\n");
    // Display each phone call in the bill with a loop
    for (PhoneCall calls : phoneCalls) {
      LocalDateTime startDateTime = calls.getBeginVar();
      LocalDateTime endDateTime = calls.getEndVar();
      if(startDateTime == null || endDateTime == null){
        System.out.println("start and end time error");
        return false;
      }
      Duration duration = Duration.between(startDateTime, endDateTime);
      long minutes = duration.toMinutes();
      System.out.println(
              "" + calls.getCaller() + "\n" + calls.getCallee() +
                      "\n" + calls.getBeginTimeString() +
                      "\n" + calls.getEndTimeString() +
                      "\n" + minutes +  " \n");


    }
    /*
    for (PhoneCall calls : phoneCalls) {

      System.out.println(
              "Caller: " + calls.getCaller() + "\nCallee: " + calls.getCallee() +
                      "\nBegin Date: " + calls.getBeginTimeString() +
                      "\nEnd Date: " + calls.getEndTimeString() +
                      " " +  "\n");

      }
      */

    return true;
  }

}