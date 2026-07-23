package edu.pdx.cs.joy.dahuynh;

import edu.pdx.cs.joy.ParserException;
import edu.pdx.cs.joy.PhoneBillParser;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.time.LocalDateTime;

import static edu.pdx.cs.joy.dahuynh.Project3.parsetime;

/**
 * A skeletal implementation of the <code>TextParser</code> class for Project 2.
 */
public class TextParser implements PhoneBillParser<PhoneBill> {
  private final Reader reader;

  public TextParser(Reader reader) {
    this.reader = reader;
  }

  @Override
  public PhoneBill parse() throws ParserException {
    try (
            BufferedReader br = new BufferedReader(this.reader)
    ) {
      // Read the customer name for the PhoneBill
      String customerName = br.readLine();
      if (customerName == null) {
        throw new ParserException("Missing customer name");
      }

      PhoneBill bill = new PhoneBill(customerName);

      String caller;
      // Loop to read all the phone calls
      System.out.println("Parsing");
      while ((caller = br.readLine()) != null) {
        String callee = br.readLine();
        String startInfo = br.readLine();
        String endInfo = br.readLine();

        if (callee == null || startInfo == null || endInfo == null) {
          if(callee == null){
            System.err.println("Calee null");
          }if(startInfo == null){
            System.err.println("StartInfo null");
          }if(endInfo == null){
            System.err.println("EndInfo null");
          }
          throw new ParserException("Missing Phone Call Arguments");
        }
        //Remove NBSP unbreakable string
        startInfo = startInfo.replaceAll("\u202F", "").replaceAll("&"+"nbsp;", "");
        endInfo = endInfo.replaceAll("\u202F", "").replaceAll("&"+"nbsp;", "");

        // Split the date and time parts
        String[] beginSplit = startInfo.split(" ");
        String[] endSplit = endInfo.split(" ");

        //Make begin / end variables for parse function
        String beginDate = beginSplit[0].substring(0,beginSplit[0].length() -1).trim();
        String beginAmPm = beginSplit[1].substring(beginSplit[1].length() - 2).trim();
        String beginTime = beginSplit[1].substring(0,beginSplit[1].length() -2).trim().replaceAll("\\s","");

        String endDate = endSplit[0].substring(0,endSplit[0].length() -1).trim();
        String endAmPm = endSplit[1].substring(endSplit[1].length() - 2).trim();
        String endTime = endSplit[1].substring(0,endSplit[1].length() -2).trim().replaceAll("\\s","");

        //create localdatetime objects
        LocalDateTime begininfostring = parsetime(beginDate, beginTime, beginAmPm.toUpperCase());
        LocalDateTime endinfostring = parsetime(endDate, endTime, endAmPm.toUpperCase());

        // Create a PhoneCall object from the parsed data
        PhoneCall call = new PhoneCall(caller, callee, begininfostring, endinfostring);
        // Add the PhoneCall to the PhoneBill
        bill.addPhoneCall(call);
      }

      //return new parsed bill
      return bill;


    } catch (IOException e) {
      throw new ParserException("While parsing phone bill text", e);
    } catch (IllegalArgumentException e) {
      throw new ParserException("Invalid phone call data", e);
    }

  }



}
