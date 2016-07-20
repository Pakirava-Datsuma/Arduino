package OneControlInterface.Model;

import javafx.beans.property.Value;

import java.util.HashSet;
import java.util.Set;

/**
 * Created by swanta on 02.07.16.
 */
public class Model {
    private static final float DEFAULT_FLOAT_MIN_VALUE = -999f;
    Set<Value> values = new HashSet<>();

    public Value getValue(String id) {
        for (Value value :
                values) {
            if (value.getName() == id) {
                return value;
            }
        }
        return null;
    }

    private InputValue getUserValue(String id) {
        for (Value value :
                values) {
            if (value.getName() == id) {
                return (InputValue)value;
            }
        }
        System.out.println(id + " not found in Model.Values");
        return null;
    }

    public <T extends ComputedValue> void add (T value){
        values.add(value);
    }

    public void increaseValue(String id) {
        getUserValue(id).incrementNewValue();
    }
    public void decreaseValue(String id) {
        getUserValue(id).decrementNewValue();
    }

    public Value addValue(Value newValue) {
        values.add(newValue);
        return newValue;
    }


}
