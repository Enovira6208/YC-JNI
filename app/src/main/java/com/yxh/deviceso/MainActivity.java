package com.yxh.deviceso;

import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.yxh.deviceso.databinding.ActivityMainBinding;


public class MainActivity extends AppCompatActivity {

    // Used to load the 'collectiondevice' library on application startup.
//    static {
//        System.loadLibrary("collectiondevice");
//    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
    }

    /**
     * A native method that is implemented by the 'collectiondevice' native library,
     * which is packaged with this application.
     */
//    public native String stringFromJNI();
}