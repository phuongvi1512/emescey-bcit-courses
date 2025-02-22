package src;
import javax.microedition.media.Manager;
import javax.microedition.media.Player;
import javax.microedition.media.control.VideoControl;
import java.lang.Exception;
import net.rim.device.api.ui.Field;
import net.rim.device.api.ui.FieldChangeListener;
import net.rim.device.api.ui.UiApplication;
import net.rim.device.api.ui.component.ButtonField;
import net.rim.device.api.ui.component.Dialog;
import net.rim.device.api.ui.component.LabelField;
import net.rim.device.api.ui.component.ObjectChoiceField;
import net.rim.device.api.ui.component.RichTextField;
import net.rim.device.api.ui.container.HorizontalFieldManager;
import net.rim.device.api.ui.container.MainScreen;
import net.rim.device.api.util.StringUtilities;

/**
 * A camera stream which is capable of taking a snapshot and saving the image as a raw byte array
 */
public class CameraStream extends UiApplication {
   /**Entry point for the program*/  
 /*    public static void main(String[] args) throws CancelException {
        CameraStream app = new CameraStream();
        app.enterEventDispatcher();
    }
*/
    /**Constructor*/
    public CameraStream(MediaController mc) throws CancelException {
        CameraScreen screen = new CameraScreen(mc);
        pushScreen(screen);
    }
}

/**GUI to display the camera screen and buttons.*/
final class CameraScreen extends MainScreen {
    /**Camera video controller.*/
    private VideoControl videoControl_;
    
    /**The field containing the feed from the camera.*/
    private Field videoField_;
    
    /**A button that captures a snapshot when it is pressed.*/
    private ButtonField photoButton_;
    
    /**A button that cancels the camera when it is pressed.*/
    private ButtonField cancelButton_;
    
    /**A byte array used to hold an image.*/
    private byte[] raw_;
        
    private MediaController mc_;

    
    /**
     * Constructor, initializes the camera and creates the GUI.
     */
    CameraScreen(MediaController mc) throws CancelException {
        this.mc_ = mc;
        //Set the title of the screen.
        setTitle(new LabelField("Trusterra Memo Log - Camera", LabelField.ELLIPSIS | LabelField.FIELD_HCENTER));
        
        
        
        //Initialize the camera object and video field.
        initializeCamera();

        //If the field was constructed successfully, create the GUI.
        if(videoField_ != null) {
            createGUI(mc);
        }
    }

    /**
     * Initializes the Player, VideoControl and VideoField.
     */
    private void initializeCamera() {
        try {
            //Create a player for the camera. This is 'the' multimedia class.
            Player player = Manager.createPlayer("capture://video");
            
            //Set the player to the REALIZED state (acquire resources)
            player.realize();
            
            //Set the player to the PREFETCH state (perform time-consuming tasks, prepare for START state)
            player.prefetch();
            
            //Grab the video control and set it to the current display.
            videoControl_ = (VideoControl)player.getControl("VideoControl");
            
            if(videoControl_ != null) {
                //Create the video field as a default GUI.
                videoField_ = (Field) videoControl_.initDisplayMode(VideoControl.USE_GUI_PRIMITIVE, "net.rim.device.api.ui.Field");
                
                //Display the video control
                videoControl_.setVisible(true);
            }
            //Set the player to the START state (running and processing data)
            player.start();
        }
        catch(Exception e) {
            Dialog.alert("ERROR " + e.getClass() + ":  " + e.getMessage());
        }
    }
    
    /**
     * Adds the VideoField and the "Snap" button to the screen.
     */
    private void createGUI(MediaController mc) throws CancelException {
        this.mc_ = mc;
        
        //Add the video field to the screen.
        add(videoField_);

        //Initialize the button used to take photos.
        photoButton_ = new ButtonField("Snap");
        photoButton_.setChangeListener(new FieldChangeListener() {
            /**
            * When the "Snap" button is pressed, take a
            * snapshot and go to a new screen to display
            * the image to the user.
            */
            public void fieldChanged(Field field, int context) {
                try {
                    //A null encoding uses the default camera encoding.
                    String encoding = null;

                    //Retrieve the raw image from the VideoControl and
                    //create a screen to display the image to the user.
                    createImageScreen(videoControl_.getSnapshot(encoding), mc_);
                }
                catch(Exception e) {
                    Dialog.alert("ERROR " + e.getClass() + ":  " + e.getMessage());
                }
            }
        });
        
        //Initialize the button used to cancel the camera.
        cancelButton_ = new ButtonField("Cancel");
        cancelButton_.setChangeListener(new FieldChangeListener() {
            /**
            * When the "Cancel" button is press, throw a Cancel exception and
            * return to the main GUI.
            */
            public void fieldChanged(Field field, int context) {
                //throw new CancelException();
            }
        });
        
        //The HorizontalFieldManager keeps the buttons in the center of
        //the screen.
        HorizontalFieldManager hfm = new HorizontalFieldManager(Field.FIELD_HCENTER);
        hfm.add(photoButton_);
        hfm.add(cancelButton_);
        
        //Add the FieldManager containing the button to the screen.
        add(hfm);
    }

    /**
     * Create a screen used to display a snapshot.
     * @param raw A byte array representing an image.
     */
    private void createImageScreen(byte[] raw, MediaController mc) {
        //Initialize the save screen.
        ImageScreen imageScreen = new ImageScreen(raw, mc);

        //Switch to the save screen.
        UiApplication.getUiApplication().pushScreen(imageScreen);
    }
    
    /**
     * Handle trackball click events.
     * @see net.rim.device.api.ui.Screen#invokeAction(int)
     */
    protected boolean invokeAction(int action) {
        boolean handled = super.invokeAction(action);
        if(!handled) {
            switch(action) {
                case ACTION_INVOKE: // Trackball click.
                    return true;
            }
        }
        return handled;
    }
}


