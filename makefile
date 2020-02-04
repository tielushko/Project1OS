make:
        (gcc -c system_call.c && gcc -c context_switch.c)

compsc: system_call
        gcc -c system_call.c

runsc: compsc
        ./system_call


compcs: context_switch
        gcc -c context_switch.c

runcs: compcs
        ./context_switch


clean:
        -rm system_call context_switch *.o
