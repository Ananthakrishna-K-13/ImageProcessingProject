package com.iiitb.imageEffectApplication.effectImplementation;

import com.iiitb.imageEffectApplication.baseEffects.SingleValueParameterizableEffect;
import com.iiitb.imageEffectApplication.libraryInterfaces.BrightnessInterface;
import com.iiitb.imageEffectApplication.exception.IllegalParameterException;
import com.iiitb.imageEffectApplication.libraryInterfaces.Pixel;
import com.iiitb.imageEffectApplication.service.LoggingService;

public class BrightnessImplementation implements SingleValueParameterizableEffect  {
    private float amount;
    public void setParameterValue(float amount ) throws IllegalParameterException{//handles exceptions for illegal parameters
        if (amount < 0 || amount > 200)
            throw new IllegalParameterException("Illegal parameter for Contrast effect");

        this.amount = amount;
    }
    public Pixel[][] apply(Pixel[][] image, String fileName, LoggingService loggingService){//calls the c++ function for brightness effect
        loggingService.addLog(fileName, "Brightness", Float.toString(amount));//adding to log
        
        return BrightnessInterface.applyBrightness(image, amount);
    }
}
