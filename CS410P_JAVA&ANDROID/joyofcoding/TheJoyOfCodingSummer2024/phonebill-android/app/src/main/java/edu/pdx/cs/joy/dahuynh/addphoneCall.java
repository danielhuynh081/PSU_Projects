package edu.pdx.cs.joy.dahuynh;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class addphoneCall extends AppCompatActivity {
    public static String newcall ="NEWCALL";
    public static String customerName = "CUSTOMER_NAME";
    private PhoneCall createCall;
    private String Customer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_addphone_call);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
    }

    public void backtoMain(View view){
       Intent intent = new Intent();
       intent.putExtra(newcall, this.createCall);
      intent.putExtra(customerName, this.Customer);
       setResult(RESULT_OK, intent);
       finish();
    }

    public void addPhoneCall(View view){
        EditText customer = findViewById(R.id.customer);
        EditText caller = findViewById(R.id.caller);
        EditText callee = findViewById(R.id.callee);
        EditText beginDate = findViewById(R.id.beginDate);
        EditText beginTime = findViewById(R.id.beginTime);
        EditText beginAmPm = findViewById(R.id.beginAmPm);
        EditText endDate = findViewById(R.id.endDate);
        EditText endTime = findViewById(R.id.endTime);
        EditText endAmPm = findViewById(R.id.endAmPm);

        this.Customer = customer.getText().toString();
        if(isEmpty(this.Customer)){
            toast("Enter value for customer");
            return;
        }
        String callerString = caller.getText().toString();
        if(isEmpty(callerString)){
            toast("Enter value for caller");
            return;
        }
        String calleeString = callee.getText().toString();
        if(isEmpty(calleeString)){
            toast("Enter value for callee");
            return;
        }
        String beginDateString = beginDate.getText().toString();
        if(isEmpty(beginDateString)){
            toast("Enter value for begin date");
            return;
        }
        String beginTimeString = beginTime.getText().toString();
        if(isEmpty(beginTimeString)){
            toast("Enter value for begin time");
            return;
        }
        String beginAmPmString = beginAmPm.getText().toString();
        if(isEmpty(beginAmPmString)){
            toast("Enter value for begin AmPm");
            return;
        }
        String endDateString = endDate.getText().toString();
        if(isEmpty(endDateString)){
            toast("Enter value for end date");
            return;
        }
        String endTimeString = endTime.getText().toString();
        if(isEmpty(endTimeString)){
            toast("Enter value for end time");
            return;
        }
        String endAmPmString = endAmPm.getText().toString();
        if(isEmpty(endAmPmString)){
            toast("Enter value for end am pm");
            return;
        }
        if(isValid(callerString, calleeString, beginDateString, beginTimeString, beginAmPmString, endDateString, endTimeString, endAmPmString)) {
            this.createCall = new PhoneCall(callerString, calleeString, beginDateString, beginTimeString, beginAmPmString, endDateString, endTimeString, endAmPmString);
        }
    backtoMain(view);

    }



    private void toast(String message) {
        Toast.makeText(this, message, Toast.LENGTH_LONG).show();
    }

    private boolean isEmpty(String string) {
        return string == null || string.isEmpty();
    }

    private boolean isValid(String caller, String callee, String BeginDate, String BeginTime, String BeginAmPm, String EndDate, String EndTime, String EndAmPm){
       boolean datecheck = checkDateTime(BeginDate, BeginTime, BeginAmPm, EndDate, EndTime, EndAmPm);
       boolean checkCallers = checkCallers(caller, callee);
        return datecheck && checkCallers;

    }

    private boolean checkCallers(String caller, String callee){
       boolean pass = true;
        if (!caller.matches("\\d{3}-\\d{3}-\\d{4}")) {
            toast("Error: special characters in the caller format, please view help\"");
            pass = false;
        }if(caller.length() > 12){
            toast("Error: too many numbers in the caller format, please view help\"");
            pass = false;
        }else if(caller.length() < 12){
            toast("Error: not enough numbers in the caller format, please view help\"");
            pass = false;
        }

        //Check Callee
        if (!callee.matches("\\d{3}-\\d{3}-\\d{4}")) {
            toast("Error: special characters in the callee format, please view help\"");
            pass = false;
        }if(callee.length() > 12){
            toast("Error: too many numbers in the callee format, please view help\"");
            pass = false;
        }else if(callee.length() < 12){
            toast("Error: not enough numbers in the callee format, please view help\"");
            pass = false;
        }



        return pass;
    }
    private boolean checkDateTime(String beginDate, String beginTime, String beginAmPm, String endDate, String endTime, String endAmPm){
        //Check Date and Time
            boolean pass = true;
            //Check Begin Date

            //Check Range
            if((beginDate.length() < 8 || beginDate.length() > 10)) {
               toast("Error: not enough numbers in the begin date format, please view help");
                pass = false;
            }

            //Format of 1/1/1111
            else if(beginDate.length() == 8){
                if(!beginDate.matches("[1-9]/[1-9]/\\d{4}")){
                    toast("Error: that date does not exist in the begin date format, please view help");
                    pass = false;
                }
            }

            //Format of 1/11/1111 or 11/1/1111
            else if(beginDate.length() == 9) {
                if (!beginDate.matches("[1-9]/([1-9]|0[1-9]|1[0-9]|2[0-9]|3[0-1])/\\d{4}") && !beginDate.matches("([1-9]|0[1-9]|1[0-2])/([1-9]|0[1-9])/\\d{4}")) {
                    toast("Error: that date does not exist in the begin date format, please view help");
                    pass = false;
                }
            }

            //Format of 11/11/1111
            else{
                if(!beginDate.matches("([1-9]|0[1-9]|1[0-2])/([1-9]|0[1-9]|1[0-9]|2[0-9]|3[0-1])/\\d{4}")) {

                    toast("Error: that date does not exist in the begin date format, please view help");
                    pass = false;
                }
            }

            //Check Begin Time

            //Check Range
            if(beginTime.length() < 4 || beginTime.length() > 5){
               if(beginTime.length() > 5){
                   toast("Error: too many numbers in the begin time format, please view help");
               }else {
                   toast("Error: too little numbers in the begin time format, please view help");
               } pass = false;
            }
            //Format of 1:11
            if(beginTime.length() ==4){
                if(!beginTime.matches("[1-9]:([0-5][0-9])")){
                    toast("Error: format is wrong in the begin time format, please view help");
                    pass = false;

                }
            }
            //Format of 11:11
            if(beginTime.length() ==5) {
                if (!beginTime.matches("(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])")){
                    toast("Error: format is wrong in the begin time format, please view help");
                    pass = false;
                }
            }

            //Check Begin AmPm
            if(beginAmPm.length() != 2){
                pass = false;
                Toast.makeText(this, "Begin Am Pm is has more/less than 2 characters", Toast.LENGTH_LONG).show();
            }
            if(!beginAmPm.toLowerCase().matches("am") && !beginAmPm.toLowerCase().matches("pm")){
                pass = false;
                Toast.makeText(this, "Begin Am Pm has incorrect input", Toast.LENGTH_LONG).show();
            }

            //Check End Date

            //Check Range
            if((endDate.length() < 8 || endDate.length() > 10)) {
                toast("Error: not enough numbers in the end date format, please view help");
                pass = false;;
            }
            //Format of 1/1/1111
            else if(endDate.length() == 8){
                if(!endDate.matches("[1-9]/[1-9]/\\d{4}")){
                    toast("Error: in the end date this date does not exist, please view help");
                    pass = false;
                }
            }
            //Format of 1/11/1111 or //Format of 11/1/1111
            else if(endDate.length() == 9) {
                if (!endDate.matches("[1-9]/([1-9]|0[1-9]|1[0-9]|2[0-9]|3[0-1])/\\d{4}") && !endDate.matches("([1-9]|0[1-9]|1[0-2])/([1-9]|0[1-9])/\\d{4}")) {
                    toast("Error: in the end date this date does not exist, please view help");
                    pass = false;
                }
            }
            //Format of 11/11/1111
            else{
                if(!endDate.matches("([1-9]|0[1-9]|1[0-2])/([1-9]|0[1-9]|1[0-9]|2[0-9]|3[0-1])/\\d{4}")) {

                    toast("Error: in the end date this date does not exist, please view help");
                    pass = false;
                }
            }

            //Check End Time

            //Check Range
            if(endTime.length() < 4 || endTime.length() > 5){
                if(endTime.length() > 5){
                    toast("Error: too many numbers in the end time format, please view help");
                }else{
                    toast("Error: too little numbers in the end time format, please view help");
                }
                pass = false;
            }
            //Format of 1:11
            if(endTime.length() ==4){
                if(!endTime.matches("[1-9]:([0-5][0-9])")){
                    toast( "Error: Format is off in the End time format, please view help");
                    pass = false;

                }
            }
            //Format of 11:11
            if(endTime.length() ==5) {
                if (!endTime.matches("(1[0-9]|2[0-3]):([0-5][0-9])")){
                    toast("Error: in the End time format, please view help");
                    pass = false;
                }
            }

        //Check End AmPm
        if(endAmPm.length() != 2){
            pass = false;
            Toast.makeText(this, "End Am Pm is has more/less than 2 characters", Toast.LENGTH_LONG).show();
        }
        if(!endAmPm.toLowerCase().matches("am") && !endAmPm.toLowerCase().matches("pm")){
            pass = false;
            Toast.makeText(this, "End Am Pm has incorrect input", Toast.LENGTH_LONG).show();
        }
            return pass;
        }

}
