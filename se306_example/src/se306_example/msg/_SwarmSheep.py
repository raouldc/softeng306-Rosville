"""autogenerated by genpy from se306_example/SwarmSheep.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class SwarmSheep(genpy.Message):
  _md5sum = "8983f0b21e77c836d3700967c5fb91b8"
  _type = "se306_example/SwarmSheep"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """float64 abs_linear_x
float64 abs_angular_z
float64 px
float64 py
float64 angle
"""
  __slots__ = ['abs_linear_x','abs_angular_z','px','py','angle']
  _slot_types = ['float64','float64','float64','float64','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       abs_linear_x,abs_angular_z,px,py,angle

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(SwarmSheep, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.abs_linear_x is None:
        self.abs_linear_x = 0.
      if self.abs_angular_z is None:
        self.abs_angular_z = 0.
      if self.px is None:
        self.px = 0.
      if self.py is None:
        self.py = 0.
      if self.angle is None:
        self.angle = 0.
    else:
      self.abs_linear_x = 0.
      self.abs_angular_z = 0.
      self.px = 0.
      self.py = 0.
      self.angle = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_5d.pack(_x.abs_linear_x, _x.abs_angular_z, _x.px, _x.py, _x.angle))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 40
      (_x.abs_linear_x, _x.abs_angular_z, _x.px, _x.py, _x.angle,) = _struct_5d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_5d.pack(_x.abs_linear_x, _x.abs_angular_z, _x.px, _x.py, _x.angle))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 40
      (_x.abs_linear_x, _x.abs_angular_z, _x.px, _x.py, _x.angle,) = _struct_5d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_5d = struct.Struct("<5d")
