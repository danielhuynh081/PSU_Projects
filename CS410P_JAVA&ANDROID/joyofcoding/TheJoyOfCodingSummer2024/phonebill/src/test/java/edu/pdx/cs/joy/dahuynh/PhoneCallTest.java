package edu.pdx.cs.joy.dahuynh;

import org.junit.jupiter.api.Test;

import java.time.LocalDateTime;

import static org.hamcrest.CoreMatchers.*;
import static org.hamcrest.MatcherAssert.assertThat;

/**
 * Unit tests for the {@link PhoneCall} class.
 *
 * You'll need to update these unit tests as you build out your program.
 */
public class PhoneCallTest {

    /**
     * This unit test will need to be modified (likely deleted) as you implement
     * your project.
     */
    @Test
    void getCustomerBillTest() {
        PhoneBill newBill = new PhoneBill("daniel");
        assertThat(newBill.getCustomer(), equalTo("daniel"));
    }


    @Test
    void getCallerStringTest() {
        LocalDateTime begintime =LocalDateTime.of(2024, 4, 4, 14, 0);
        LocalDateTime endtime =LocalDateTime.of(2024, 4, 4, 14, 0);

        PhoneCall tester = new PhoneCall("555-555-5555", "444-444-4444", begintime, endtime);
        assertThat(tester.getCaller(), equalTo("555-555-5555"));
    }

    @Test
    void getCalleeStringTest() {
        LocalDateTime begintime =LocalDateTime.of(2024, 4, 4, 14, 0);
        LocalDateTime endtime =LocalDateTime.of(2024, 4, 4, 14, 0);

        PhoneCall tester = new PhoneCall("555-555-5555", "444-444-4444", begintime, endtime);
        assertThat(tester.getCallee(), equalTo("444-444-4444"));
    }
/*
    @Test
    void getBeginStringTest() {
        LocalDateTime begintime =LocalDateTime.of(2024, 4, 4, 14, 0);
        LocalDateTime endtime =LocalDateTime.of(2024, 4, 4, 14, 0);

        PhoneCall tester = new PhoneCall("555-555-5555", "444-444-4444", begintime, endtime);

        assertThat(tester.getBeginTimeString(), equalTo("4/4/24, 2:00 PM"));
    }
*/




}

