package OneControlInterface.Model.Model;

/**
 * Created by swanta on 01.07.16.
 */
public class UserDefinedValue extends Value {
    protected float step;
    protected float valueMin = Float.MIN_VALUE;
    protected float valueMax = Float.MAX_VALUE;
    protected Float value;
    protected Float newValue;

    public UserDefinedValue(float valueMin, String caption, float value, float step, float valueMax) {
        super(caption, value);
        this.valueMax = valueMax;
        this.step = step;
        this.valueMin = valueMin;
        setValue(value);
        setNewValue(value);
    }

    public UserDefinedValue(String caption, float value, float step) {
        this(Float.MIN_VALUE, caption, value, step, Float.MAX_VALUE);
    }
    public UserDefinedValue(String caption, float value) {
        this(caption, value, 0);
    }

    public UserDefinedValue(float valueMin, String caption, float value, float step) {
        this(valueMin, caption, value, step, Float.MAX_VALUE);
    }

    public UserDefinedValue(String caption, float value, float step, float valueMax) {
        this(Float.MIN_VALUE, caption, value, step, valueMax);
    }

    void setValue(float value) {
        float newValue = filterValue(value);
        if (value != newValue) {
            this.value = newValue;
        }
    }

    void setNewValue(float newValue) {
        float newNewValue = filterValue(newValue);
        if (newNewValue != newValue) {
            this.newValue = newNewValue;
        }
    }

    void applyNewValue () {
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

    void incrementNewValue(int times) {
        setNewValue((Float) value + step * times);
    }

    void decrementNewValue(int times) {
        setNewValue(value - step * times);
    }

    String getTextLineNew() {
        return getTextLine(newValue);
    }

    @Override
    public void saveNewValue() {
//        User shall modify this value only through LineTextInterface.Model.View.Menu
    }
}
