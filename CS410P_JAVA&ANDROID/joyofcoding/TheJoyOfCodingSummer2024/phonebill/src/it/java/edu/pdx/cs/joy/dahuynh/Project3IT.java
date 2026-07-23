package edu.pdx.cs.joy.dahuynh;

import edu.pdx.cs.joy.InvokeMainTestCase;
import org.junit.jupiter.api.Test;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Tests the functionality in the {@link Project3} main class.
 */
class Project3IT extends InvokeMainTestCase {

    /**
     * Invokes the main method of {@link Project3} with the given arguments.
     */
    private MainMethodResult invokeMain(String... args) {
        return invokeMain( Project3.class, args );
    }

  /**
   * Tests that invoking the main method with no arguments issues an error
   */
  @Test
  void testSevenCommandLineArgument() {
      Project3 tester = new Project3();
      String[] args = {"Name", "555-555-5555", "444-444-4444", "12/12/2000", "12:12", "12/22/2002", "12:12"};
      tester.checkArguments(args);
      assertFalse(tester.checkArguments(args));

  }
/*
    @Test
    void testSevenCommandLineArgument() {
        Project3 tester = new Project3();
        String[] args = {"Name", "555-555-5555", "444-444-4444", "12/12/2000", "12:12", "12/22/2002", "12:12"};
        tester.checkArguments(args);
        assertTrue(tester.checkArguments(args));

    }
    @Test
    void testFailedFlagCommandLineArgument() {
        MainMethodResult result = invokeMain("6", "Name","555-555-5555", "444-444-4444"," 5/2/2000", "12:12", "5/2/2022", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("6 must be a valid argument, there are extraneous arguments"));

    }

    @Test
    void testCallerCommandLineArgument() {
        MainMethodResult result = invokeMain("Name","55-555-5555", "444-444-4444","5/2/2000", "12:12", "5/2/2022", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the caller format, there are too many numbers used, please use the option -README for more information"));

    }

    @Test
    void testCalleeCommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "44-444-4444","5/2/2000", "12:12", "5/2/2022", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the callee format, there are not enough numbers used, please use the option -README for more information"));

    }

    @Test
    void testBeginDateLengthCommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6253/2/2000", "12:12", "5/2/2022", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the begin date format, theres not enough numbers, please use the -README option for more help"));

    }
    @Test
    void testBeginDate2CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","62/2/2000", "12:12", "5/2/2022", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the begin date format, this day does not exist, please use the -README option for more help"));

    }

    @Test
    void testBeginDate3CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","0/2/2000", "12:12", "5/2/2022", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the begin date format, this date does not exist, please use the -README option for more help"));

    }
    @Test
    void testBeginDate4CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","0/0/2000", "12:12", "5/2/2022", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the begin date format, this date does not exist, please use the -README option for more help"));

    }

    @Test
    void testBeginDate5CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","00/00/0000", "12:12", "5/2/2022", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the begin date format,  this day does not exist, please use the -README option for more help"));

    }

    @Test
    void testBeginDate6CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","0/2", "12:12", "5/2/2022", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the begin date format, theres not enough numbers, please use the -README option for more help"));

    }
    @Test
    void testBeginTimeCommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "24:12", "5/2/2022", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the begin time format, this time isn't supported on the 24 hour clock, please use the -README option for more help"));

    }

    @Test
    void testBeginTime2CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "24:12", "5/2/2022", "1:92");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the begin time format, this time isn't supported on the 24 hour clock, please use the -README option for more help\n" +
                "There was an error in the End time format, this time isn't supported on the 24 hour clock, please use the -README option for more help"));

    }

    @Test
    void testBeginTime3CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "24:12", "5/2/2022", "24:92");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the begin time format, this time isn't supported on the 24 hour clock, please use the -README option for more help\n" +
                "There was an error in the End time format, this time isn't supported on the 24 hour clock, please use the -README option for more help"));

    }

    @Test
    void testBeginTime4CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "24:12", "5/2/2022", "248:92");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the begin time format, this time isn't supported on the 24 hour clock, please use the -README option for more help\n" +
                "There was an error in the End time format, the number placement is off, please use the -README option for more help"));

    }

    @Test
    void testBeginTime5CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "24:12", "5/2/2022", "24892");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the begin time format, this time isn't supported on the 24 hour clock, please use the -README option for more help\n" +
                "There was an error in the End time format, this time isn't supported on the 24 hour clock, please use the -README option for more help"));

    }

    @Test
    void testBeginTime6CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "24:12", "5/2/2022", "24892");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the begin time format, this time isn't supported on the 24 hour clock, please use the -README option for more help\n" +
                "There was an error in the End time format, this time isn't supported on the 24 hour clock, please use the -README option for more help"));

    }

    @Test
    void testEndDateLengthCommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "12:12", "2/2/222", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the end date format, theres not enough numbers, please use the -README option for more help"));

    }

    @Test
    void testEndDate2CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "12:12", "22/2/2222", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the end date format, this date does not exist, please use the -README option for more help"));

    }

    @Test
    void testEndDate3CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "12:12", "0/2/2222", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the end date format, this date does not exist, please use the -README option for more help"));

    }

    @Test
    void testEndDate4CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "12:12", "2/0/2222", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the end date format, this date does not exist, please use the -README option for more help"));

    }

    @Test
    void testEndDate5CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "12:12", "2/0/0000", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the end date format, this date does not exist, please use the -README option for more help"));

    }

    @Test
    void testEndDate6CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "12:12", "2", "12:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the end date format, theres not enough numbers, please use the -README option for more help"));

    }
    @Test
    void testEndTimeCommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "23:12", "5/2/2022", "24:12");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the End time format, this time isn't supported on the 24 hour clock, please use the -README option for more help"));

    }

    @Test
    void testEndTime2CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "23:12", "5/2/2022", "4:92");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the End time format, this time isn't supported on the 24 hour clock, please use the -README option for more help"));

    }

    @Test
    void testEndTime3CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "23:12", "5/2/2022", "24:972");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the End time format, the number placement is off, please use the -README option for more help"));

    }

    @Test
    void testEndTime4CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "23:12", "5/2/2022", "324:72");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the End time format, the number placement is off, please use the -README option for more help"));

    }

    @Test
    void testEndTime5CommandLineArgument() {
        MainMethodResult result = invokeMain("Name","555-555-5555", "454-444-4444","6/2/2000", "23:12", "5/2/2022", "32472");
        assertThat(result.getTextWrittenToStandardError(), containsString("There was an error in the End time format, this time isn't supported on the 24 hour clock, please use the -README option for more help"));

    }
*/
}
