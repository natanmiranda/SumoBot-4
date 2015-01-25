'
'  Author: Rodman, vitalijrodnov@gmail.com
'  motor control subs are taken from www.barello.net
'  compiler: BascomAVR at www.mcselec.com
'-------------------------------------------------------------------------------------
$regfile = "m16def.dat"
$crystal = 10000000
 
Dim Cycles As Word
Dim Obj As Integer
Dim I As Word , J As Word
Dim Range As Byte , Gain As Byte
Dim L_lsb As Byte , L_msb As Byte
Dim R_lsb As Byte , R_msb As Byte
Dim L_range As Word , L_distance As Word
Dim R_range As Word , R_distance As Word
Declare Sub Spin
Declare Sub Sonar_init
Declare Sub L_motor(byval Pwm As Integer)
Declare Sub R_motor(byval Pwm As Integer)
Config Adc = Single , Prescaler = Auto , Reference = Avcc
Start Adc
 
L_340_1 Alias Pina.3 : Config Pina.3 = Input                'additional GP2Y0D340K sensors
L_340_2 Alias Pind.7 : Config Pind.7 = Input
L_340_3 Alias Pinc.2 : Config Pinc.2 = Input
R_340_1 Alias Pina.2 : Config Pina.2 = Input
R_340_2 Alias Pinb.1 : Config Pinb.1 = Input
R_340_3 Alias Pinb.4 : Config Pinb.4 = Input
 
L_line_out Alias Pinc.0 : Config Portc.0 = Input            'Left  LINE out(INT1)
R_line_out Alias Pinc.1 : Config Portc.1 = Input            'Right LINE out(INT0)
 
L_motor_pwm Alias Pwm1b : Config Portd.4 = Output           'Left  motors PWM(OC1A)
R_motor_pwm Alias Pwm1a : Config Portd.5 = Output           'Right motors PWM(OC1B)
L_motor_dir Alias Portd.3 : Config Portd.3 = Output         'Left  motors DIR
R_motor_dir Alias Portd.6 : Config Portd.6 = Output         'Right motors DIR
Config Timer1 = Pwm , Pwm = 8 ,Compare A Pwm = Clear Up ,Compare B Pwm = Clear Up ,Prescale = 8
R_motor_pwm = 0 : R_motor 0
L_motor_pwm = 0 : L_motor 0
Config Scl = Portd.2
Config Sda = Portd.1
Sonar_init
Wait 5
Enable Interrupts
 
If L_340_2 = 0 Then                                         'enemy detected on the left side
   L_motor -255 : R_motor 255
   Cycles = 200
   Call Spin                                                'spins CW/CCW after Start
Else
   L_motor 255 : R_motor -255
   Cycles = 200
   Call Spin
End If
 
Do
'----------------------------GP2D12 Left and Right------------------------------
R_range = Getadc(5)
L_range = Getadc(4)
If R_range > 120 Then Obj.4 = 1
If L_range > 120 Then Obj.5 = 1
 
'----------------------------TCRT1000 Left and Right----------------------------
If L_line_out = 1 Then
   L_motor -200 : R_motor -200 : Waitms 200
   L_motor 200 : R_motor -200 : Waitms 200
End If
 
If R_line_out = 1 Then
   L_motor -200 : R_motor -200 : Waitms 200
   L_motor -200 : R_motor 200 : Waitms 200
End If
'----------------------------GP2Y0D340K SHARPS ---------------------------------
If R_340_3 = 0 Then Obj.0 = 1
If R_340_2 = 0 Then Obj.1 = 1
If R_340_1 = 0 Then Obj.3 = 1
 
If L_340_1 = 0 Then Obj.6 = 1
If L_340_2 = 0 Then Obj.8 = 1
If L_340_3 = 0 Then Obj.9 = 1
 
'----------------------------SRF08 Left and Right-------------------------------
I2cstart : I2cwbyte 0 : I2cwbyte 0 : I2cwbyte 81 : I2cstop
Waitms 20
I2cstart : I2cwbyte 224 : I2cwbyte 2
I2cstart : I2cwbyte 225 : I2crbyte L_msb , Ack : I2crbyte L_lsb , Nack : I2cstop
L_distance = Makeint(l_lsb , L_msb)
I2cstart : I2cwbyte 226 : I2cwbyte 2
I2cstart : I2cwbyte 227 : I2crbyte R_msb , Ack : I2crbyte R_lsb , Nack : I2cstop
R_distance = Makeint(r_lsb , R_msb)
 
If R_distance <= 50 Then Obj.2 = 1
If L_distance <= 50 Then Obj.7 = 1
 
'----------------------------EVALUATION-----------------------------------------
Select Case Obj
   Case 0
      L_motor 150 : R_motor 150                             'nothing
'-----------------------------
   Case 1                                                   'R3_340 back-right
      L_motor 255 : R_motor -255
      Cycles = 300
      Call Spin
'-----------------------------
   Case 2                                                   'R2_340 side-right
      L_motor 255 : R_motor -255
      Cycles = 200
      Call Spin
'-----------------------------
   Case 4
      L_motor 255 : R_motor -255                            'R_ultrasonic side-right
      Cycles = 200
      Call Spin
'-----------------------------
   Case 128
      L_motor -255 : R_motor 255                            'L_ultrasonic side-left
      Cycles = 200
      Call Spin
'-----------------------------
   Case 256                                                 'L2_340 side-left
      L_motor -255 : R_motor 255
      Cycles = 200
      Call Spin
'-----------------------------
   Case 512                                                 'L3_340 back-left
      L_motor -255 : R_motor 255
      Cycles = 300
      Call Spin
'-----------------------------
   Case 8 To 120                                            ' any combination of front sensors
      If L_line_out = 1 Then                                'line detection priority
         L_motor -200 : R_motor -200 : Waitms 200
         L_motor 200 : R_motor -200 : Waitms 200
      End If
 
      If R_line_out = 1 Then
         L_motor -200 : R_motor -200 : Waitms 200
         L_motor -200 : R_motor 200 : Waitms 200
      End If
      L_motor 255 : R_motor 255
'-----------------------------
   Case 6                                                   'R2_340 + R_ultrasonic
      L_motor 255 : R_motor -255
      Cycles = 200
      Call Spin
'-----------------------------
   Case 384                                                 'L2_340 + L_ultrasonic
      L_motor -255 : R_motor 255
      Cycles = 200
      Call Spin
'-----------------------------
   Case 513                                                 'L3_340 + R3_340
      L_motor -255 : R_motor 255
      Cycles = 300
      Call Spin
'-----------------------------
 
End Select
'-------------------------------------------------------------------------------
Obj = 0
Loop
 
 
 
End
 
   Sub Spin
      For I = 1 To Cycles
      For J = 1 To Cycles
         If L_340_1 = 0 Then Goto Exit_spin
         If R_340_1 = 0 Then Goto Exit_spin
      Next J
      Next I
      Exit_spin:
   End Sub
 
 
   Sub Sonar_init
   I2cinit
   Range = 60
      I2cstart : I2cwbyte 224 : I2cwbyte 2 : I2cwbyte Range : I2cstop
      I2cstart : I2cwbyte 226 : I2cwbyte 2 : I2cwbyte Range : I2cstop
   Gain = 30
      I2cstart : I2cwbyte 224 : I2cwbyte 1 : I2cwbyte Gain : I2cstop
      I2cstart : I2cwbyte 226 : I2cwbyte 1 : I2cwbyte Gain : I2cstop
   End Sub
 
 
   Sub L_motor(byval Pwm As Integer)
       If Pwm >= 0 Then
           L_motor_dir = 0
           Tccr1a.com1b0 = 0                                'normal PWM
       Else
           L_motor_dir = 1
           Tccr1a.com1b0 = 1
           Pwm = -pwm                                       'inverted PWM
       End If
       L_motor_pwm = Pwm
   End Sub
 
 
   Sub R_motor(byval Pwm As Integer)
       If Pwm >= 0 Then
           R_motor_dir = 0
           Tccr1a.com1a0 = 0                                'normal PWM
       Else
           R_motor_dir = 1
           Tccr1a.com1a0 = 1
           Pwm = -pwm                                       'inverted PWM
       End If
       R_motor_pwm = Pwm
   End Sub
 



 




