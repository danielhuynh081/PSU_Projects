package edu.pdx.cs.joy.dahuynh;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class printCalls extends AppCompatActivity {
    private ArrayAdapter<String> calls;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_print_calls);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });


        this.calls=new ArrayAdapter<>(this,android.R.layout.simple_list_item_1, new ArrayList<>());
        ListView listView = findViewById(R.id.calls);
        listView.setAdapter(this.calls);

        Intent intent = getIntent();

        if(intent.hasExtra("CUSTOMER_NAME") && intent.hasExtra("NEW_CALL") && !intent.hasExtra("SEARCH")) {
            PhoneCall newCall = (PhoneCall) intent.getSerializableExtra("NEW_CALL");
            String customerName = intent.getStringExtra("CUSTOMER_NAME");
                if (newCall != null) {
                    Toast.makeText(this, "customername and newcall entered", Toast.LENGTH_LONG).show();

                    this.calls.add("Customer: "+customerName+ newCall.FormString());
                    try {
                        readCallsFromFile(null);
                    }catch(IOException e){
                        Toast.makeText(this,"while reading bills" + e.getMessage(), Toast.LENGTH_LONG).show();
                    }
                    try {
                        writeCallsToFile(newCall, customerName);
                    }catch(IOException e){
                        Toast.makeText(this,"while writing bills" + e.getMessage(), Toast.LENGTH_LONG).show();
                    }

                }
        }
        if(intent.hasExtra("SEARCH")){
            try {
                String customerName = intent.getStringExtra("SEARCH");
                Toast.makeText(this, "search case entered", Toast.LENGTH_LONG).show();
                Toast.makeText(this, customerName, Toast.LENGTH_LONG).show();

                readCallsFromFile(customerName);
            }catch(IOException e){
                Toast.makeText(this,"while reading bills" + e.getMessage(), Toast.LENGTH_LONG).show();
            }
        }
        if(!intent.hasExtra("CUSTOMER_NAME") && !intent.hasExtra("NEW_CALL") && !intent.hasExtra("SEARCH")) {
            try {
                Toast.makeText(this, "no customer entered", Toast.LENGTH_LONG).show();
                readCallsFromFile(null);
            }catch(IOException e){
                Toast.makeText(this,"while reading bills" + e.getMessage(), Toast.LENGTH_LONG).show();
            }
        }
        Toast.makeText(this, "no cases met", Toast.LENGTH_LONG).show();




    }

    private void readCallsFromFile(String Search) throws IOException {
        File Callsfile = getCallsFile();
        try(BufferedReader br = new BufferedReader(new FileReader(Callsfile))){
            for(String line = br.readLine(); line!= null; line = br.readLine()){
                String customer = line;
                if(Search != null){
                    Toast.makeText(this,"searh not null", Toast.LENGTH_LONG).show();
                    if(line.toLowerCase().contains(("Customer: " + Search).toLowerCase())){

                            this.calls.add(customer);

                    }
                }
                if(Search == null) {
                    if (this.calls.getPosition(customer) == -1) {
                        this.calls.add(customer);
                    }
                }
            }
        }

    }

    private void writeCallsToFile(PhoneCall newCall, String customerName) throws IOException {
        File callFiles = getCallsFile();
        try(PrintWriter pw = new PrintWriter(new FileWriter(callFiles))){
            for(int i =0; i<this.calls.getCount(); i++){
                String bill = this.calls.getItem(i);
                pw.println(bill);
            }
            pw.flush();

        }

    }


    private File getCallsFile(){
            return new File(this.getDataDir(), "calls.txt");
    }

    public void backtoMain(View view) {
        finish();
    }
}