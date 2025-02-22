/*
 * ButtonListenner.java
 *
 * � <your company here>, 2003-2008
 * Confidential and proprietary.
 */

package src;
import java.lang.Exception;
import net.rim.device.api.ui.FieldChangeListener;
import net.rim.device.api.ui.Field;
import net.rim.device.api.ui.component.ButtonField;
import net.rim.device.api.ui.component.Status;
import net.rim.device.api.ui.UiApplication;


/**
 * 
 */
public final class ButtonListener implements FieldChangeListener {
    private MediaController mc;
    
    public void fieldChanged(Field field, int context){
        String btnLabel;
        int button;
        //button acton handler
        ButtonField btn = (ButtonField)field;
        btnLabel = btn.getLabel();

        if (btnLabel.equals(Menu.IMAGE_BTNLABEL)){
            button = Menu.IMAGE;
            processButton(button,btn);
            }
        if (btnLabel.equals(Menu.AUDIO_BTNLABEL)){
            button = Menu.AUDIO;
            processButton(button,btn);
            }
        if (btnLabel.equals(Menu.VIDEO_BTNLABEL)){
            button = Menu.VIDEO;
            processButton(button,btn);
            } 
        if (btnLabel.equals(Menu.CANCEL_BTNLABEL)){
            button = Menu.CANCEL;
            processButton(button,btn);
            }
        if (btnLabel.equals(Menu.SEND_BTNLABEL)){
            button = Menu.SEND;
            processButton(button,btn);
            }
        
    }
    
    void processButton(int button,ButtonField btn){
        mc = new MediaController();
        switch (button){

            case Menu.SEND:
                LoginScreen ls = new LoginScreen();
                UiApplication.getUiApplication().pushScreen(ls);
                break;
            case Menu.VIDEO:
                Status.show("Video Field will be implemented.");

                break;
            case Menu.AUDIO:
                //Status.show("Button pressed: " + btn.getLabel());
                SalutationScreen ss = new SalutationScreen(mc);
                UiApplication.getUiApplication().pushScreen(ss);
                break;
            case Menu.CANCEL:
                Status.show("Button pressed: " + btn.getLabel());
                break;
            case Menu.IMAGE:
                CameraStream cs = new CameraStream(mc);
                UiApplication.getUiApplication().pushScreen(cs);
            default:
                break;
   
        }
    }
} 

