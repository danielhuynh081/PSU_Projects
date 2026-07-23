package edu.pdx.cs.joy.dahuynh;

import edu.pdx.cs.joy.AbstractPhoneCall;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.FormatStyle;


public class PhoneCall extends AbstractPhoneCall implements Comparable<PhoneCall> {
    //Data Variables
    private final String caller;
    private final String callee;
    private final LocalDateTime beginDateTime;
    //  private final String beginAmPm;
    private final LocalDateTime endDateTime;
//  private final String endAmPm;


    //Constructor
    public PhoneCall(String caller, String callee, LocalDateTime beginDateTime,  LocalDateTime endDateTime) {
        this.caller= caller;
        this.callee = callee;
        this.beginDateTime = beginDateTime;
        // this.beginAmPm = beginAmPm;
        this.endDateTime = endDateTime;
        // this.endAmPm = endAmPm;
    }
    @Override
    public String getCaller() {
        return this.caller;
    }

    //Callee Getter Test
    @Override
    public String getCallee() {
        return this.callee;
    }

    //Begin Date Getter Test
  /*public String getBeginString() {
    return this.beginDateTime;
  }
*/
    LocalDateTime getBeginVar(){
        return this.beginDateTime;
    }

    LocalDateTime getEndVar(){
        return this.endDateTime;
    }
    //Begin Time Getter Test
    @Override
    public String getBeginTimeString(){
        DateTimeFormatter formatter = DateTimeFormatter.ofLocalizedDateTime(FormatStyle.SHORT);
        String beginstring = beginDateTime.format(formatter);
        return beginstring;
    }
    /*//End Date Getter Test
    public String getEndString() {
      return this.end;
    }
  */
    //End Time Getter Test
    @Override
    public String getEndTimeString() {
        DateTimeFormatter formatter = DateTimeFormatter.ofLocalizedDateTime(FormatStyle.SHORT);
        String endstring = endDateTime.format(formatter);
        return endstring;
    }

    @Override
    public int compareTo(PhoneCall phoneCall) {
        int dateTimeComparison = this.beginDateTime.compareTo(phoneCall.beginDateTime);

        if (dateTimeComparison != 0) {
            return dateTimeComparison; // If different, return the result of date-time comparison
        }

        // If beginDateTime is the same, compare by caller
        return this.caller.compareTo(phoneCall.caller);

    }
}