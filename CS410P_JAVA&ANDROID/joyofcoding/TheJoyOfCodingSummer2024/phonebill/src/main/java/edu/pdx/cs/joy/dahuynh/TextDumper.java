package edu.pdx.cs.joy.dahuynh;


import edu.pdx.cs.joy.PhoneBillDumper;

import java.io.*;

/**
 * A skeletal implementation of the <code>TextDumper</code> class for Project 2.
 */
public class TextDumper implements PhoneBillDumper<PhoneBill> {
  private final Writer writer;
  public TextDumper(Writer writer) {
    this.writer = writer;
  }

  @Override
  public void dump(PhoneBill bill) {
    try (
            BufferedWriter pw = new BufferedWriter(this.writer);
    ) {
      System.out.println("Inserting/Replacing new bill into the textfile.\n\nPrinting updated text file");
      pw.write( bill.getCustomer() + "\n");
      for (PhoneCall calls : bill.getPhoneCalls()) {
        pw.write(

                calls.getCaller() + "\n" + calls.getCallee() +
                        "\n" + calls.getBeginTimeString() +
                        "\n" + calls.getEndTimeString() +
                        "\n");
      }
      pw.close();
      bill.printPhone();
      System.out.println("New file saved\n");
    } catch (IOException e) {
      throw new RuntimeException(e);
    }

  }
}