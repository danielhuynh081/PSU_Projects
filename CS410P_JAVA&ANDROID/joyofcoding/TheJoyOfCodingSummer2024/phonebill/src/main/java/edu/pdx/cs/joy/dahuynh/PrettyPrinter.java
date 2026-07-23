package edu.pdx.cs.joy.dahuynh;

import edu.pdx.cs.joy.PhoneBillDumper;

import java.time.LocalDateTime;
import java.io.BufferedWriter;
import java.time.Duration;
import java.time.LocalDateTime;
import java.io.IOException;
import java.io.Writer;

public class PrettyPrinter implements PhoneBillDumper<PhoneBill> {

    private final Writer writer;


    public PrettyPrinter(Writer writer){
        this.writer = writer;
    }

    @Override
    public void dump(PhoneBill bill) throws IOException {
        try (
                BufferedWriter pw = new BufferedWriter(this.writer);
        ) {
            System.out.println("Pretty printing new bill into the textfile.\n\nPrinting updated text file");

            pw.write( "Customer: "+bill.getCustomer() + "\n");

            for (PhoneCall calls : bill.getPhoneCalls()) {
                LocalDateTime startDateTime = calls.getBeginVar();
                LocalDateTime endDateTime = calls.getEndVar();
                Duration duration = Duration.between(startDateTime, endDateTime);
                pw.write(

                        "Caller: " + calls.getCaller() + "\nCallee: " + calls.getCallee() +
                                "\nBegin Date: " + calls.getBeginTimeString() +
                                "\nEnd Date: " + calls.getEndTimeString() +
                                "\nDuration: " + duration.toMinutes() +  "\n");
            }
            pw.close();
            bill.printPhone();
            System.out.println("New file saved\n");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }



    }
    public void prettyprint(PhoneBill bill) throws IOException {
        if(bill.getPhoneCalls() == null) {
            System.err.println("\nEmpty phone bill");

        }else{

            for (PhoneCall calls : bill.getPhoneCalls()) {
                LocalDateTime startDateTime = calls.getBeginVar();
                LocalDateTime endDateTime = calls.getEndVar();
                Duration duration = Duration.between(startDateTime, endDateTime);
                System.out.println("Customer: "+bill.getCustomer() + "\n");

                System.out.println(
                        "Caller: " + calls.getCaller() + "\nCallee: " + calls.getCallee() +
                                "\nBegin Date: " + calls.getBeginTimeString() +
                                "\nEnd Date: " + calls.getEndTimeString() +
                                "\nDuration: " + duration.toMinutes() +  " Minutes \n");


            }
        }
    }
}