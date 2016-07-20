package OneControlInterface.Model;

import javafx.beans.binding.FloatBinding;
import javafx.beans.property.SimpleFloatProperty;

import java.util.Random;

public abstract class ComputedValue extends FloatBinding implements Value{
    protected String name;
    protected SimpleFloatProperty value;
    private float step;
    private float valueMaximum;
    private float valueMinimum;


    public ComputedValue(String name) {
        System.out.println("создаю объект под "+ name);
        this.value = new SimpleFloatProperty(this, name, -999f);
    }

    public String getTextLine() {
        return getTextLine(value);
    }
    String getTextLine(SimpleFloatProperty value) {
        return name + ":" + value.getValue();
    }

//    public float getValue() {
//        return value.getValue();
//    }

    public String getName() {
        return name;
    }

    public static float random(float base){
        Random random = new Random();
        return base + random.nextFloat()*2-1;
    }
    public static int random(int bound){
        Random random = new Random();
        return random.nextInt(bound);
    }
//    void randomize(){
//        value = ComputedValue.random(2f);
//    }
    public void saveNewValue(){}

}
