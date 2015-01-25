$regfile = "m8def.dat"
$crystal = 10000000
Wait 5
 
Dim Cycles As Integer
Dim I As Byte , J As Byte , Obj As Byte
 
Right_motor_dir Alias Portb.0 : Config Pinb.0 = Output
Right_motor_pwm Alias Pwm1a : Config Pinb.1 = Output
 
Left_motor_dir Alias Portd.7 : Config Pind.7 = Output
Left_motor_pwm Alias Pwm1b : Config Pinb.2 = Output
 
Front Alias Pind.0 : Config Pind.0 = Input
Front_left Alias Pind.2 : Config Pind.2 = Input
Front_right Alias Pind.1 : Config Pind.1 = Input
 
Left_line Alias Pinc.3 : Config Pinc.3 = Input
Right_line Alias Pinc.4 : Config Pinc.4 = Input
 
Const Motor_forward = 0
Const Motor_reverse = 1
Declare Sub Spin
Declare Sub Set_left_motor_pwm(byval Pwm As Integer)
Declare Sub Set_right_motor_pwm(byval Pwm As Integer)
 
Config Timer1 = Pwm , Pwm = 8 , Compare A Pwm = Clear Down , Compare B Pwm = Clear Down , Prescale = 8
 
If Front_left = 0 Then                                      'spin if side sensor sees enemy
   Set_left_motor_pwm -250                                  'in the beginning of the fight
   Set_right_motor_pwm 250
   Cycles = 30000
   Call Spin
   Else
   Set_left_motor_pwm 250
   Set_right_motor_pwm -250
   Cycles = 30000
   Call Spin
End If
 
 
Do
 
If Left_line = 1 Then                                       'line detected- go back and turn around
   Set_left_motor_pwm -200
   Set_right_motor_pwm -200
   Waitms 300
   Set_left_motor_pwm 250
   Set_right_motor_pwm -250
   Waitms 100
End If
 
If Right_line = 1 Then                                      'line detected- go back and turn around
   Set_left_motor_pwm -200
   Set_right_motor_pwm -200
   Waitms 300
   Set_left_motor_pwm -250
   Set_right_motor_pwm 250
   Waitms 100
End If
 
If Front_right = 0 Then Obj.0 = 1
If Front = 0 Then Obj.1 = 1
If Front_left = 0 Then Obj.2 = 1
 
Select Case Obj
   Case 0                                                   'nothing detected-go straight
      Set_left_motor_pwm 80
      Set_right_motor_pwm 80
   Case 1                                                   'right sensor sees object-turn right
      Set_left_motor_pwm 250
      Set_right_motor_pwm -250
      Cycles = 30000
      Call Spin
   Case 2                                                   'front sees object-full speed forward
      Set_left_motor_pwm 250
      Set_right_motor_pwm 250
   Case 4                                                   'left sensor sees object-turn left
      Set_left_motor_pwm -250
      Set_right_motor_pwm 250
      Cycles = 30000
      Call Spin
End Select
 
Obj = 0
Loop
 
 
End
 
Sub Spin
   For I = 1 To Cycles
      For J = 1 To Cycles
      If Left_line = 1 Then                                 'check line just to make sure
         Set_left_motor_pwm -200
         Set_right_motor_pwm -200
         Waitms 300
         Set_left_motor_pwm 250
         Set_right_motor_pwm -250
         Waitms 100
         Goto Exit_spin
      End If
      If Right_line = 1 Then                                'check line just to make sure
         Set_left_motor_pwm -200
         Set_right_motor_pwm -200
         Waitms 300
         Set_left_motor_pwm -250
         Set_right_motor_pwm 250
         Waitms 100
         Goto Exit_spin
      End If
      If Front = 0 Then Goto Exit_spin                      'exit sub if enemy detected
      Next J
   Next I
   Exit_spin:
End Sub
 
Sub Set_left_motor_pwm(byval Pwm As Integer)
    If Pwm >= 0 Then
        Left_motor_dir = Motor_forward
        Tccr1a.com1b0 = 0                                   'normal PWM
    Else
        Left_motor_dir = Motor_reverse
        Tccr1a.com1b0 = 1
        Pwm = -pwm                                          'inverted PWM
    End If
    Left_motor_pwm = Pwm
End Sub
 
Sub Set_right_motor_pwm(byval Pwm As Integer)
    If Pwm >= 0 Then
        Right_motor_dir = Motor_forward
        Tccr1a.com1a0 = 0                                   'normal PWM
    Else
        Right_motor_dir = Motor_reverse
        Tccr1a.com1a0 = 1
        Pwm = -pwm                                          'inverted PWM
    End If
    Right_motor_pwm = Pwm
End Sub
