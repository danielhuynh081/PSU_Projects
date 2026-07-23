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

public class phoneBillPrint extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_phone_bill_print);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });


    }

    public void printCallers(View view){
        EditText customer = findViewById(R.id.editTextText);
        String customerString = customer.getText().toString();
        Toast.makeText(this, customerString, Toast.LENGTH_LONG).show();
        Intent intent = new Intent(this, printCalls.class);
        if(customerString != null) {
            intent.putExtra("SEARCH", customerString);
        }
        Toast.makeText(this, "Printcallers called", Toast.LENGTH_LONG).show();
        startActivity(intent);
    }


}