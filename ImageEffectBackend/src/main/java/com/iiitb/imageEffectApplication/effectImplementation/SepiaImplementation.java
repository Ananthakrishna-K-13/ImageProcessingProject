package com.iiitb.imageEffectApplication.effectImplementation;

import com.iiitb.imageEffectApplication.baseEffects.PhotoEffect;
import com.iiitb.imageEffectApplication.libraryInterfaces.Pixel;
import com.iiitb.imageEffectApplication.libraryInterfaces.SepiaInterface;
import com.iiitb.imageEffectApplication.service.LoggingService;

public class SepiaImplementation implements PhotoEffect {//applying the effect and adding to log
    public Pixel[][] apply(Pixel[][] image, String fileName, LoggingService loggingService){
        loggingService.addLog(fileName,"Sepia","None");
        return SepiaInterface.applySepia(image);
    }
}
