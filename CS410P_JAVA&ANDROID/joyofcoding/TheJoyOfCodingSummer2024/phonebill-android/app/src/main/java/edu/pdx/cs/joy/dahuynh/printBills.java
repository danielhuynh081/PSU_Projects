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
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class printBills extends AppCompatActivity {
private ArrayAdapter<String> bills ;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_print_bills);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

    this.bills=new ArrayAdapter<>(this,android.R.layout.simple_list_item_1, new ArrayList<>());
    ListView listView = findViewById(R.id.bills);
    listView.setAdapter(this.bills);

    Intent intent = getIntent();
    if(intent.hasExtra("CUSTOMER_NAME")) {
        String customerName = intent.getStringExtra("CUSTOMER_NAME");
        this.bills.add(customerName);
    }
    try {
        readSumsFromFile();
    }catch(IOException e){
        Toast.makeText(this,"while reading bills" + e.getMessage(), Toast.LENGTH_LONG).show();
    }
        try {
            writeSumsToFile();
        }catch(IOException e){
            Toast.makeText(this,"while writing bills" + e.getMessage(), Toast.LENGTH_LONG).show();
        }

    }

    private void readSumsFromFile() throws IOException {
        File billsfile = getBillsFile();
        try(BufferedReader br = new BufferedReader(new FileReader(billsfile))){
            for(String line = br.readLine(); line!= null; line = br.readLine()){
                String customer = line;
               if(this.bills.getPosition(customer) ==-1) {
                   this.bills.add(customer);
               }
            }
        }


    }

    private void writeSumsToFile() throws IOException {
        File billFiles = getBillsFile();
        try(PrintWriter pw = new PrintWriter(new FileWriter(billFiles))){
            for(int i =0; i<this.bills.getCount(); i++){
                String bill = this.bills.getItem(i);
                  pw.println(bill);
            }
            pw.flush();

        }

    }

    private File getBillsFile() {
        return new File(this.getDataDir(), "bills.txt");
    }

    public void backtoMain(View view) {
        finish();
    }
}