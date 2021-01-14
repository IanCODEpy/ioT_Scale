package com.example.ledcontrolfirebase;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {
    Button on;
    Button off;
    TextView weight;
    TextView percent;
    DatabaseReference dref;
    String status2;
    String status;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        on = (Button) findViewById(R.id.btn_on);
        off = (Button) findViewById(R.id.btn_off);
        weight = (TextView) findViewById(R.id.txt_weight);
        percent = (TextView) findViewById(R.id.txt_percent);

        dref = FirebaseDatabase.getInstance().getReference();
        dref.addValueEventListener(new ValueEventListener() {
           @Override
          public void onDataChange(DataSnapshot dataSnapshot) {
             status = dataSnapshot.child("Weight").getValue().toString();
                weight.setText(status);
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {
           }
        });
        dref.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                status2 = dataSnapshot.child("percent").getValue().toString();
                percent.setText(status2);
            }
            @Override
            public void onCancelled(DatabaseError databaseError) {
            }
        });

        on.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                FirebaseDatabase database = FirebaseDatabase.getInstance();
                DatabaseReference myRef = database.getReference("emergency");

                myRef.setValue(1);
            }
        });
        off.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                FirebaseDatabase database = FirebaseDatabase.getInstance();
                DatabaseReference myRef = database.getReference("emergency");

                myRef.setValue(0);
            }
        });
    }
}
