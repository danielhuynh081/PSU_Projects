package edu.pdx.cs.joy.dahuynh;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import java.io.Serializable;
import java.time.Duration;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class phoneBillActivity extends AppCompatActivity {
private List<PhoneBill> phonebills = new ArrayList<PhoneBill>();

private static final int GET_CALL = 42;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_phone_bill);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
    }

    public void launchAddPhoneCalls(View view) {
        // Toast.makeText(this, "Opening Help", Toast.LENGTH_LONG).show();
        Intent intent = new Intent(this, addphoneCall.class);
        startActivityForResult(intent, GET_CALL);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        //After creating new call
        if (requestCode == GET_CALL) {
            //Check if the call was successfuly created
            if (resultCode == RESULT_OK && data != null) {
                boolean matchfound=false;
                String customerName = data.getStringExtra("CUSTOMER_NAME");
                PhoneCall newCall = (PhoneCall) data.getSerializableExtra(addphoneCall.newcall);
             //Call and bill are not null
                if (newCall != null && customerName != null) {
                    //Open activity to pick phonebill
                    if(phonebills.isEmpty()){
                        PhoneBill newBill = new PhoneBill(customerName);
                        newBill.addCall(newCall);
                        phonebills.add(newBill);
                        Toast.makeText(this, "First bill, New Bill created with new call", Toast.LENGTH_LONG).show();
                        matchfound = true;
                    }
                    for (PhoneBill bills : phonebills) {
                        if (Objects.equals(bills.getCustomer(), customerName) && !matchfound) {
                            Toast.makeText(this, "Match Found", Toast.LENGTH_LONG).show();
                            bills.addCall(newCall);
                            matchfound = true;
                        }
                    }
                    if(!matchfound){
                        PhoneBill newBill = new PhoneBill(customerName);
                        newBill.addCall(newCall);
                        phonebills.add(newBill);
                        Toast.makeText(this, "Couldn't find match so New Bill created with new call", Toast.LENGTH_LONG).show();
                    }

                    Toast.makeText(this, "Printing bill infomration", Toast.LENGTH_LONG).show();
                    Toast.makeText(this,"Printing all bills", Toast.LENGTH_LONG).show();
                    //add customer to bill name list
                    Intent intent = new Intent(this, printBills.class);
                    intent.putExtra("CUSTOMER_NAME", customerName);
                    startActivity(intent);
                    Intent intent2 = new Intent(this, printCalls.class);
                    intent2.putExtra("NEW_CALL", (Serializable) newCall);
                    intent2.putExtra("CUSTOMER_NAME", customerName);
                    startActivity(intent2);
                }
                if (newCall == null) {
                    Toast.makeText(this, "New Call Error", Toast.LENGTH_LONG).show();
                } else if (customerName == null) {
                    Toast.makeText(this, "Customer Name Error", Toast.LENGTH_LONG).show();
                }
            }
        }
    }






    public void launchHelp(View view) {
        // Toast.makeText(this, "Opening Help", Toast.LENGTH_LONG).show();
        Intent intent = new Intent(this, helpActivity.class);
        startActivity(intent);
    }

    public void backtoMain(View view){
        finish();
    }

    public void launchprintBills(View view) {
        Intent intent = new Intent(this, printBills.class);
        startActivity(intent);
    }

    public void launchPrintCalls(View view){
        Intent intent = new Intent(this, phoneBillPrint.class);
        startActivity(intent);
    }

}