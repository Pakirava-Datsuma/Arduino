package OneControlInterface.Model;

import javafx.beans.property.SimpleFloatProperty;

/**
 * Created by swanta on 01.07.16.
 */
public class InputValue implements Value{
    protected SimpleFloatProperty value;
    protected String name;

    public InputValue(String caption, float value) {
        System.out.println("создаю объект под "+ name);
        this.value = new SimpleFloatProperty(this, name, value);
        setValue(value);
   }

    public InputValue(String caption) {
        this(caption, 0f);
    }
     void setValue(float value) {
         this.value.setValue(value);
     }

    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public Float getValue() {
        return value.getValue();
    }

    @Override
    public String getTextLine() {
        return name + ":" + value.getValue();
    }

    //    String getTextLineNew() {
//        return getTextLine(newValue);
//    }

}
