package OneControlInterface.Model.Model;

import java.util.HashSet;
import java.util.Set;

/**
 * Created by swanta on 02.07.16.
 */
public class Model {
    Set<Value> values = new HashSet<>();

    public Value getValue(String id) {
        for (Value value :
                values) {
            if (value.caption == id) {
                return value;
            }
        }
        return null;
    }

    public UserDefinedValue getUserValue(String id) {
        for (Value value :
                values) {
            if (value.caption == id) {
                return (UserDefinedValue)value;
            }
        }
        return null;
    }

    public <T extends Value> void add (T value){
        values.add(value);
    }

    public void increaseValue(String id) {
        getUserValue(id).incrementNewValue();
    }
    public void decreaseValue(String id) {
        getUserValue(id).decrementNewValue();
    }
}
