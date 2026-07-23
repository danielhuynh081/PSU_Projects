package edu.pdx.cs.joy.dahuynh;

import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.io.StringWriter;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.containsString;

public class PrettyPrintTest {
    /***testing class for Pretty Print Function***/
        @Test
        void phoneBillOwnerIsDumpedInTextFormat() throws IOException {
            String customer = "Test Phone Bill";
            PhoneBill bill = new PhoneBill("Test Phone Bill" );

            StringWriter sw = new StringWriter();
           PrettyPrinter dumper = new PrettyPrinter(sw);
            dumper.dump(bill);

            String text = sw.toString();
            assertThat(text, containsString(customer));
        }

}
