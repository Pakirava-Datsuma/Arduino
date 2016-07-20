package OneControlInterface.Model;

import javafx.beans.property.SimpleFloatProperty;

/**
 * Created by swanta on 20.07.16.
 */
public class UserInputValue extends InputValue {

    protected float step;
    protected float valueMin = Float.MIN_VALUE;
    protected float valueMax = Float.MAX_VALUE;
    protected float newValue;

    public UserInputValue(String caption, float value, float step) {
        this(Float.MIN_VALUE, caption, value, step, Float.MAX_VALUE);
    }

    public UserInputValue(float valueMin, String caption, float value, float step) {
        this(valueMin, caption, value, step, Float.MAX_VALUE);
    }

    public UserInputValue(String caption, float value, float step, float valueMax) {
        this(Float.MIN_VALUE, caption, value, step, valueMax);
    }


    public UserInputValue(float valueMin, String caption, float value, float step, float valueMax) {
        super(caption, value);
        this.valueMax = valueMax;
        this.step = step;
        this.valueMin = valueMin;
        setNewValue(value);
    }

    void setNewValue(float newValue) {
        float newNewValue = filterValue(newValue);
        if (newNewValue != newValue) {
            this.newValue = newNewValue;
        }
    }

    void applyNewValue () {
//        User shall modify this value only through LineTextInterface.Model.View.Menu
        setValue(newValue);
    }

    private float filterValue(float value) {
        return Math.min(valueMin, Math.max(valueMax, value));
    }

    void incrementNewValue() {
        incrementNewValue(1);
    }

    void decrementNewValue() {
        decrementNewValue(1);
    }

    private void incrementNewValue(int times) {
        setNewValue((float) value.getValue() + step * times);
    }

    private void decrementNewValue(int times) {
        setNewValue(value.getValue() - step * times);
    }

}
