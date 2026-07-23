package edu.pdx.cs.joy.dahuynh;

import org.junit.jupiter.api.Test;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import static org.hamcrest.CoreMatchers.*;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * A unit test for code in the <code>Project3</code> class.  This is different
 * from <code>Project3IT</code> which is an integration test (and can capture data
 * written to {@link System#out} and the like.
 */
class Project3Test {

  @Test
  void readmeCanBeReadAsResource() throws IOException {
    try (
            InputStream readme = Project3.class.getResourceAsStream("README.txt")
    ) {
      assertThat(readme, not(nullValue()));
      BufferedReader reader = new BufferedReader(new InputStreamReader(readme));
      String line = reader.readLine();
      assertThat(line, containsString("This is a README file!"));
    }
  }


  @Test
  void checkNULLFormatTest() {
    String [] args ={null};
    Project3 tester = new Project3();

    assertFalse(tester.checkArguments(args));
  }
  @Test
  void checkFormatTest() {
    String [] args ={"dave", "555-555-5555", "444-444-4444", "12/12/2000", "12:12", "PM", "12/22/2002", "12:12", "am"};
    Project3 tester = new Project3();

    assertTrue(tester.checkFormat(args));
  }

  @Test
  void checkCallerTest() {
    String [] args ={"dave","5155-555-5555", "444-444-4444", "12/12/2000", "12:12", "pm", "12/22/2002", "12:12", "am"};
    Project3 tester = new Project3();

    assertFalse(tester.checkFormat(args));
  }

  @Test
  void checkCallerTest2() {
    String [] args ={"dave","5525-5525-5555", "444-444-4444", "12/12/2000", "12:12", "pm", "12/22/2002", "12:12", "am"};
    Project3 tester = new Project3();

    assertFalse(tester.checkFormat(args));
  }

  @Test
  void checkCallerTest3() {
    String [] args ={"dave","555555-5555", "444-444-4444", "12/12/2000", "12:12", "pm", "12/22/2002", "12:12", "am"};
    Project3 tester = new Project3();

    assertFalse(tester.checkFormat(args));
  }

  @Test
  void checkCalleeTest() {
    String [] args ={"555-555-5555", "444-4444", "12/12/2000", "12:12", "pm", "12/22/2002", "12:12", "am"};
    Project3 tester = new Project3();

    assertFalse(tester.checkFormat(args));
  }

  @Test
  void checkCalleeTest2() {
    String [] args ={"555-555-5555", "444-444 -4444", "12/12/2000", "12:12", "pm", "12/22/2002", "12:12", "am"};
    Project3 tester = new Project3();

    assertFalse(tester.checkFormat(args));
  }

  @Test
  void checkCalleeTest3() {
    String [] args ={"555-555-5555", "444-@44-4444", "12/12/2000", "12:12", "pm", "12/22/2002", "12:12", "am"};
    Project3 tester = new Project3();

    assertFalse(tester.checkFormat(args));
  }

  @Test
  void checkDateFormatTest() {
    String [] args ={"555-555-5555", "444-444-4444", "12/12/2000", "12:12", "pm", "12/22/2002", "12:12", "am"};
    Project3 tester = new Project3();

    assertTrue(tester.checkDateFormat(args));
  }

  @Test
  void checkDateFormat2Test() {
    String [] args ={"555-555-5555", "444-4444", "1212/2000", "12:12", "pm", "12/22/2002", "12:12", "am"};
    Project3 tester = new Project3();

    assertFalse(tester.checkDateFormat(args));
  }

  @Test
  void checkDateFormat3Test() {
    String [] args ={"555-555-5555", "444-4444", "1/0/2000", "12:12","pm", "12/22/2002", "12:12","am"};
    Project3 tester = new Project3();

    assertFalse(tester.checkDateFormat(args));
  }

  @Test
  void checkDateFormat4Test() {
    String [] args ={"555-555-555", "444-4444", "0/0/2/2000", "12:12","pm", "12/22/2002", "12:12","am"};
    Project3 tester = new Project3();

    assertFalse(tester.checkDateFormat(args));
  }

  @Test
  void checkDateFormat5Test() {
    String [] args ={"555-55-5555", "444-4444", "0/0/0000", "12:12", "pm", "12/22/2002", "12:12", "am"};
    Project3 tester = new Project3();

    assertFalse(tester.checkDateFormat(args));
  }
  @Test
  void checkDateFormat6Test() {
    String [] args ={"555-5-5555", "444-4444", "0/000", "12:12", "am","12/22/2002", "12:12","pm"};
    Project3 tester = new Project3();

    assertFalse(tester.checkDateFormat(args));
  }

  @Test
  void checkArgumentsTest() {
    String [] args ={"david", "555-555-5555", "444-444-4444", "2/2/2000", "12:12", "pm","12/22/2002", "12:12", "am"};
    Project3 tester = new Project3();

    assertTrue(tester.checkArguments(args));
  }

  @Test
  void checkArguments2Test() {
    String [] args ={"555-555-5555", "444-444-4444", "2/2/2000", "12:12", "pm", "12/22/2002"};
    Project3 tester = new Project3();

    assertFalse(tester.checkArguments(args));
  }

  @Test
  void checkArguments3Test() {
    String [] args ={"555-555-5555", "444-444-4444", "2/2/2000", "12:12", "12/22/2002", "12:12", "5", "5", "5"};
    Project3 tester = new Project3();

    assertFalse(tester.checkArguments(args));
  }
  @Test
  void checkprintTest() {
    String [] args ={"555-555-5555", "444-444-4444", "2/2/2000", "12:12", "12/22/2002", "12:12", "-print"};
    Project3 tester = new Project3();

    assertFalse(tester.checkArguments(args));
  }


  @Test
  void readmeFlagTest() {
    String [] args ={"-readme","daniel", "555-555-5555", "444-444-4444", "12/12/2000", "12:12", "pm", "12/22/2002", "12:12","am"};
    Project3 tester = new Project3();

    assertTrue(tester.checkArguments(args));
  }


  @Test
  void constructorTest() {
    Project3 tester = new Project3();

    assertTrue(tester != null);
  }

  @Test
  void validDateFormatTest() {
    String [] args ={"daniel", "555-555-5555", "444-444-4444", "12/12/2000", "12:12","am", "12/22/2002", "12:12","am"};
    Project3 tester = new Project3();

    assertTrue(tester.checkDateFormat(args));
  }

  @Test
  void validTimeFormatTest() {
    String [] args ={"daniel", "555-555-5555", "444-444-4444", "12/12/2000", "12:12", "pm", "12/22/2002", "12:12", "am"};
    Project3 tester = new Project3();

    assertTrue(tester.checkDateFormat(args));
  }

  @Test
  void phoneNumberWithSpacesTest() {
    String [] args ={"555 555 5555", "444-444-4444", "12/12/2000", "12:12", "pm", "12/22/2002", "12:12","am"};
    Project3 tester = new Project3();

    assertFalse(tester.checkFormat(args));
  }

  @Test
  void phoneNumberWithSpecialCharactersTest() {
    String [] args ={"555-555-555!", "444-444-4444", "12/12/2000", "12:12", "pm", "12/22/2002", "12:12", "am"};
    Project3 tester = new Project3();

    assertFalse(tester.checkFormat(args));
  }
/*
  @Test
  void printPhoneCallsTest(){
    LocalDateTime begintime =LocalDateTime.of(2024, 4, 4, 14, 0);
    LocalDateTime endtime =LocalDateTime.of(2024, 4, 4, 14, 0);
    PhoneBill bill = new PhoneBill("Wally");
    PhoneCall tester = new PhoneCall("555-555-5555", "444-444-4444", begintime, endtime);
    bill.addPhoneCall(tester);
    assertTrue(bill.printPhone());
  }
*/


}
