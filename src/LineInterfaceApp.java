import OneControlInterface.Model.*;
import OneControlInterface.Model.LineTextInterface;
import javafx.beans.InvalidationListener;
import javafx.beans.Observable;

import java.util.Scanner;

import static java.lang.System.currentTimeMillis;

/**
 * Created by swanta on 25.06.16.
 */
public class LineInterfaceApp{

    public static void main(String[] args) {

        Model model = new Model();

        Value sysTime = model.addValue(
                new ComputedValue("time_on") {
                    @Override
                    protected float computeValue() {
                        return currentTimeMillis()/1000;
                    }
                });
        Value sysTimeLoop = model.addValue(
                new ComputedValue("t_loop") {
                    private float oldTime = sysTime.getValue();
                    @Override
                    protected float computeValue() {
                        float newTime = sysTime.getValue();
                        this.value.set(newTime - this.oldTime);
                        this.oldTime = newTime;
                        return this.value.getValue();
                    }
                });
        Value actualTemperature = model.addValue(new Thermometer("T"));
        Value maximumLimitTemperature = model.addValue(
                new UserInputValue("T_max", 14f, 0.1f));
        Value tempWindow = model.addValue(
                new UserInputValue(0f, "dt", 2f, 0.1f));
        Value engineState = model.addValue(
                new ComputedValue("engineStatus") {
                    {
                        value.set(-1f);
                    }
                    @Override
                    protected float computeValue() {
                        float result;
                        float t = actualTemperature.getValue();
                        float tmax = maximumLimitTemperature.getValue();
                        float dt = tempWindow.getValue();
                        float state = Math.signum(value.getValue());
                        if (    (   (state > 0)
                                    && (t < tmax - dt))
                                || ((state < 0)
                                    && (t > tmax))){
                            value.set(-value.getValue());
                        }
                        return value.getValue();
                    }
                });
        Value engineTimeOn = model.addValue(
                new ComputedValue("engineTimeOn") {
                    {
                        super.bind(model.getValue(engineState.getName()));
                        this.addListener(
                                new InvalidationListener() {
                                    @Override
                                    public void invalidated(Observable observable) {
                                        if (engineState.getValue() > 0f)
                                            value.set(sysTime.getValue());
                                    }
                                }
                        );
                    }
                    @Override
                    protected float computeValue() {
                        return value.getValue();
                    }
                });
        Value engineTimeLast = model.addValue(
                new ComputedValue("engineTimeLast") {
//                    TODO bind to engineState
                    @Override
                    protected float computeValue() {
                        return value.getValue();
                    }
                });
        Value engineTimeTotal =  model.addValue(
                new ComputedValue("engineTimeTotal") {
                    @Override
                    protected float computeValue() {
                        return currentTimeMillis()/1000;
                    }
                });
        Value engineTimeOff = model.addValue(
                new ComputedValue("engineTimeOff") {
                    @Override
                    protected float computeValue() {
                        return currentTimeMillis()/1000;
                    }
                });
        Value engineConsumptionTotal = model.addValue(
                new ComputedValue("p_engine_Total") {
                    @Override
                    protected float computeValue() {
                        return currentTimeMillis()/1000;
                    }
                });
        Value engineConsumptionPerHour = model.addValue(
                new UserInputValue(0.1f, "p_engine_const", 2f, 0.1f));
        Value engineConsumptionDaily = model.addValue(
                new ComputedValue("P_t") {
                    @Override
                    protected float computeValue() {
                        return currentTimeMillis()/1000;
                    }
                });
        Value engineEffect = model.addValue(
                new ComputedValue("P_eff") {
                    @Override
                    protected float computeValue() {
                        return currentTimeMillis()/1000;
                    }
                });

        String menuConfig =
        "0<Температура внутри<" + actualTemperature.getName()
            +"|1<Статус"
                +"|2=Время последнего сеанса="+ engineTimeLast.getName()
                +"|2=Включился="+ engineTimeOn.getName()
                +"|2=Выключился="+ engineTimeOff.getName()
            +"|1<Статистика"
                +"|2=Время от сети=t="+ sysTime.getName()
                +"|2=Время мотора=t.м="+engineTimeTotal.getName()
                +"|2=Мощн с начала=кВт="+ engineConsumptionTotal.getName()
                +"|2=Мощн в день=кВт/1день="+ engineConsumptionDaily.getName()
                +"|2=Эффект=кВт/1град="+ engineEffect.getName()
                +"|2>Потребление мотора=кВт/ч="+ engineConsumptionTotal.getName()
            +"|1<Настройки"
                +"|2>температура включения>C>" + maximumLimitTemperature.getName()
                +"|2>Температурное окно>C>"+ tempWindow.getName()
                +"|2>Потребление мотора>кВт/ч>"+ engineConsumptionTotal.getName()

                ;

        LineTextInterface iface = new LineTextInterface(16, 2, menuConfig, model);

        Relay relay = new Relay(engineState);
        Scanner scanner = new Scanner(System.in);

        boolean exit = false;
        do { //loop
            actualTemperature.setValue(thermometer.getTemperature());
            sysTime.setValue(sys currentTimeMillis()/1000;


            if (actualTemperature > maximumLimitTemperature && engineState < 0.5)
                TRIG_engineOn:{

                    relay.enable();
                    engineTimeOn = sysTime;
                    engineState = 1f;

                }
            else if (actualTemperature < (maximumLimitTemperature - tempWindow) && engineState > 0.5)

                TRIG_engineOff:{

                    relay.disable();
                    engineTimeOff = currentTimeMillis();
                    engineTimeLast = engineTimeOff - engineTimeOn;
                    engineTimeTotal += engineTimeLast;
                    engineTimeOff = 0l;
                    engineConsumptionTotal = (engineTimeTotal / sysTime )*1f;
                    engineConsumptionDaily = engineConsumptionTotal/ (24 * 3600);
                    engineEffect = engineTimeLast / tempWindow;
                    engineState = 0f;
            }
            while (!scanner.hasNextInt()) {
                if (engineState == 0.0) {

                }

            }
            iface.updateScreen();
            int input = scanner.nextInt();
            switch (input) {
                case 1:
                    iface.doHome();
                    break;
                case 5:
                    iface.doNext();
                    break;
                case 4:
                    iface.doEnter();
                    break;
                case 3:
                    iface.doBack();
                    break;
                case 2:
                    iface.doPrev();
                    break;
                default:
                    exit = true;
                    break;
            }


        } while (!exit);


    }

    private static class Relay {

        public void disable() {
            System.out.println("Relay off");
        }

        public void enable() {
            System.out.println("Relay ON");
        }
    }

    private static class Thermometer {
        private ComputedValue temperature;
        protected ComputedValue Thermometer (String name){
            temperature = new ComputedValue(name) {
                @Override
                protected float computeValue() {
                    return getTemperature();
                }
            };
            return temperature;
        }
        public Float getTemperature() {
            return ComputedValue.random(temperature.getValue());
        }
    }
}


