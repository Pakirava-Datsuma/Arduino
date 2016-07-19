package OneControlInterface.Model;

import OneControlInterface.Model.Model.Model;
import OneControlInterface.Model.Model.UserDefinedValue;
import OneControlInterface.Model.Model.Value;
import OneControlInterface.Model.View.View;

/**
 * Created by swanta on 02.07.16.
 */
public class LineTextInterface {
    private Model model ;
    private View view ;

    public LineTextInterface(int screenLines, int screenCharsInLine, String menuConfig) {
        view = new View(screenLines, screenCharsInLine, menuConfig);
        model = view.getModel();
    }

    public <T extends Value> void addValue(T value) {
        model.add(value);
    }

    public void updateScreen () {
        view.update();
    }

    public void doEnter() {
        view.doEnter();
    }

    public void doBack() {
       view.doBack();
    }

    public void doNext() {
        view.doNext();
    }

    public void doPrev() {
        view.doPrev();
    }

    public void doHome() {
        view.doHome();
    }

}
