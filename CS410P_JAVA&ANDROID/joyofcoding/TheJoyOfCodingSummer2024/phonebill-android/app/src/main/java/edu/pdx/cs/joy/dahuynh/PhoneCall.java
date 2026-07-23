package edu.pdx.cs.joy.dahuynh;

import java.io.Serializable;
import java.time.LocalDateTime;

import edu.pdx.cs.joy.AbstractPhoneCall;

public class PhoneCall extends AbstractPhoneCall implements Serializable {
    private final String caller;
    private final String callee;
    private final String beginDateTime;
    private final String endDateTime;
public PhoneCall(String caller, String callee, String beginDate, String beginTime, String beginAmPm,  String endDate, String endTime, String endAmPm) {
    this.caller= caller;
    this.callee = callee;
    this.beginDateTime = beginDate + ", " + beginTime+ beginAmPm.toUpperCase();
    this.endDateTime = endDate +  ", " + endTime + endAmPm;
}

    public String getCaller() {
    return this.caller;
    }
    public String getCallee() {
 return this.callee;
    }
    public String getBeginTimeString() {
    return this.beginDateTime;
}
    public String getEndTimeString() {
return this.endDateTime;
    }
    public String FormString(){
        return  " Caller: " + getCaller()  +" Callee: "+ getCallee() + " Begin Time: " + getBeginTimeString()+ " End Time: " + getEndTimeString();
    }
}
