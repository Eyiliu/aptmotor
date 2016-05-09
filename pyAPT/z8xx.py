from controller import Controller



class Z8xx(Controller):
  """
  A controller for a Z8xx.
  """
  def __init__(self,*args, **kwargs):
    super(Z8xx, self).__init__(*args, **kwargs)

    enccnt = 34304
    T = 2048/6e6

    self.position_scale = enccnt
    self.velocity_scale = enccnt * T * 65536
    self.acceleration_scale = enccnt * T * T * 65536

    self.linear_range = (0,25)


    ##
    self.max_velocity = 2.3
    self.max_acceleration = 4.0
    ## TODO : max_velocity max_acceleration 

# MoterEW = Z8xx(serial_number="83848096")
# MoterSN = Z8xx(serial_number="83848103")
# MoterDU = Z8xx(serial_number="83848929")
