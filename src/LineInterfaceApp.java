import OneControlInterface.Model.LineTextInterface;
import OneControlInterface.Model;

import java.util.Scanner;

import static java.lang.System.currentTimeMillis;

/**
 * Created by swanta on 25.06.16.
 */
public class LineInterfaceApp{

    public static void main(String[] args) {

        final String str_temp = "T";
        Float temp = 12f;
        final String str_tempMax = "T_max";
        Float tempMax = 14f;
        final String str_tempWindow = "dt";
        Float tempWindow = 2f;

        final String str_sysTime = "time_on";
        Long sysTime= Long.valueOf(0);
        final String str_sysTimeLoop = "t_loop";
        Long sysTimeLoop = Long.valueOf(0);

        final String str_engineTimeLast =  "engineTimeLast";
        Long engineTimeLast;
        final String str_engineTimeTotal =  "engineTimeTotal";
        Long engineTimeTotal = Long.valueOf(0);
        final String str_engineTimeOn = "engineTimeOn";
        Long engineTimeOn = Long.valueOf(0);
        final String str_engineTimeOff = "engineTimeOff";
        Long engineTimeOff = Long.valueOf(0);
        final String str_engineConsumptionTotal = "p_engine_Total";
        Float engineConsumptionTotal = 0f;
        final String str_engineConsumptionPerHour = "p_engine_const";
        Float engineConsumptionPerHour = 2f;
        final String str_engineConsumptionDaily = "P_t";
        Float engineConsumptionDaily = 0f;
        final String str_engineEffect = "P_eff";
        Float engineEffect = 0f;
        final String str_engineState = "engineStatus";
        Float engineState = 0f;

        String menuConfig =
        "0<Температура внутри<" +str_temp +
            "|1<Настройки" +
                "|2>температура включения>" + str_tempMax+
                "|2>Температурное окно>"+ str_tempWindow+
            "|1<Статистика" +
                "|2=Время от сети=t="+str_sysTime+
                "|2=Время мотора=t.м="+
                "|2=Мощн с начала=P="+str_engineConsumptionTotal+
                "|2=Мощн в день=P/день="+str_engineConsumptionDaily+
                "|2=Эффект=P/град="+str_engineEffect;
        LineTextInterface iface = new LineTextInterface(16, 2, menuConfig);
        iface.addValue(new Value(str_temp, temp));
        iface.addValue(new Value (str_engineState, engineState));
        iface.addValue(new Value (str_engineTimeTotal, engineTimeTotal));
        iface.addValue(new Value (str_engineTimeOn, engineTimeOn));
        iface.addValue(new Value (str_engineTimeOff, engineTimeOff));
        iface.addValue(new UserDefinedValue(str_tempMax, tempMax, 13f, 0.1f));
        iface.addValue(new UserDefinedValue (0f, str_tempWindow, tempWindow , 2f, 0.1f));
        iface.addValue(new UserDefinedValue (0.1f, str_engineConsumptionPerHour, engineConsumptionPerHour, 1f, 0.1f));
        iface.addValue(new Value (str_sysTimeLoop, sysTimeLoop));
        iface.addValue(new Value (str_sysTime, sysTime));
        iface.addValue(new Value (str_engineConsumptionTotal, engineConsumptionTotal));
        iface.addValue(new Value (str_engineConsumptionDaily, engineConsumptionDaily));
        iface.addValue(new Value (str_engineEffect, engineEffect));
        Relay relay = new Relay();
        Scanner scanner = new Scanner(System.in);
        boolean exit = false;
        do { //loop
            Thermometer thermometer = new Thermometer();
            temp = thermometer.getTemperature(temp);
            sysTime += currentTimeMillis()/1000;


            if (temp > tempMax && engineState < 0.5)
                TRIG_engineOn:{

                    relay.enable();
                    engineTimeOn = sysTime;
                    engineState = 1f;

                }
            else if (temp < (tempMax - tempWindow) && engineState > 0.5)

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
        public Float getTemperature(Float temp) {
            return Value.random(temp);
        }
    }
}


