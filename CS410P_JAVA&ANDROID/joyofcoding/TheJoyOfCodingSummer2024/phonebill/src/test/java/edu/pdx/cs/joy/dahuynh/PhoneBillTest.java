package edu.pdx.cs.joy.dahuynh;

import org.junit.jupiter.api.Test;
import java.time.LocalDateTime;
import java.util.Collection;

import static org.hamcrest.CoreMatchers.equalTo;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.hasItem;
import static org.hamcrest.Matchers.hasSize;

public class PhoneBillTest {

    @Test
    void getCustomerBillTest() {
        PhoneBill newBill = new PhoneBill("daniel");
        assertThat(newBill.getCustomer(), equalTo("daniel"));
    }

    @Test
    void getCustomerBillWithFullNameTest() {
        PhoneBill newBill = new PhoneBill("daniel huynh");
        assertThat(newBill.getCustomer(), equalTo("daniel huynh"));
    }

    @Test
    void getCustomerBillWithNullNameTest() {
        PhoneBill newBill = new PhoneBill(null);
        assertThat(newBill.getCustomer(), equalTo(null));
    }

    @Test
    void addPhoneCallTest() {
        LocalDateTime begintime =LocalDateTime.of(2024, 4, 4, 14, 0);
        LocalDateTime endtime =LocalDateTime.of(2024, 4, 4, 14, 0);

        PhoneCall tester = new PhoneCall("555-555-5555", "444-444-4444", begintime, endtime);
        PhoneBill newBill = new PhoneBill("daniel");
        newBill.addPhoneCall(tester);
        assertThat(newBill.getPhoneCalls(), hasItem(tester));
    }

    @Test
    void getPhoneCallTest() {
        LocalDateTime begintime =LocalDateTime.of(2024, 4, 4, 14, 0);
        LocalDateTime endtime =LocalDateTime.of(2024, 4, 4, 14, 0);

        PhoneCall tester = new PhoneCall("555-555-5555", "444-444-4444", begintime, endtime);
        PhoneBill newBill = new PhoneBill("daniel");
        newBill.addPhoneCall(tester);
        Collection<PhoneCall> calllog = newBill.getPhoneCalls();
        assertThat(calllog, hasItem(tester));
    }

    @Test
    void newPhoneBillShouldHaveNoPhoneCalls() {
        PhoneBill newBill = new PhoneBill("daniel");
        assertThat(newBill.getPhoneCalls(), hasSize(0));
    }

    @Test
    void addMultiplePhoneCallsTest() {
        LocalDateTime begintime =LocalDateTime.of(2024, 4, 4, 14, 0);
        LocalDateTime endtime =LocalDateTime.of(2024, 4, 4, 14, 0);

        PhoneCall call1 = new PhoneCall("555-555-5555", "444-444-4444", begintime, endtime);
        PhoneCall call2 = new PhoneCall("455-555-5555", "444-444-4444", begintime, endtime);

        PhoneBill newBill = new PhoneBill("daniel");
        newBill.addPhoneCall(call1);
        newBill.addPhoneCall(call2);
        assertThat(newBill.getPhoneCalls(), hasSize(2));
        assertThat(newBill.getPhoneCalls(), hasItem(call1));
        assertThat(newBill.getPhoneCalls(), hasItem(call2));
    }



}
