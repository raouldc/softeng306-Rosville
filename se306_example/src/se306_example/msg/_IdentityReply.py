"""autogenerated by genpy from se306_example/IdentityReply.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class IdentityReply(genpy.Message):
  _md5sum = "309a8015d7d85889db9d2cae74c5019f"
  _type = "se306_example/IdentityReply"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """string sender
string destination
string type
int32 height
float32 abs_cmd_vel_linear_x
float32 abs_cmd_vel_angular_z

"""
  __slots__ = ['sender','destination','type','height','abs_cmd_vel_linear_x','abs_cmd_vel_angular_z']
  _slot_types = ['string','string','string','int32','float32','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       sender,destination,type,height,abs_cmd_vel_linear_x,abs_cmd_vel_angular_z

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(IdentityReply, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.sender is None:
        self.sender = ''
      if self.destination is None:
        self.destination = ''
      if self.type is None:
        self.type = ''
      if self.height is None:
        self.height = 0
      if self.abs_cmd_vel_linear_x is None:
        self.abs_cmd_vel_linear_x = 0.
      if self.abs_cmd_vel_angular_z is None:
        self.abs_cmd_vel_angular_z = 0.
    else:
      self.sender = ''
      self.destination = ''
      self.type = ''
      self.height = 0
      self.abs_cmd_vel_linear_x = 0.
      self.abs_cmd_vel_angular_z = 0.

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
      _x = self.sender
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.destination
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.type
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_i2f.pack(_x.height, _x.abs_cmd_vel_linear_x, _x.abs_cmd_vel_angular_z))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.sender = str[start:end].decode('utf-8')
      else:
        self.sender = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.destination = str[start:end].decode('utf-8')
      else:
        self.destination = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.type = str[start:end].decode('utf-8')
      else:
        self.type = str[start:end]
      _x = self
      start = end
      end += 12
      (_x.height, _x.abs_cmd_vel_linear_x, _x.abs_cmd_vel_angular_z,) = _struct_i2f.unpack(str[start:end])
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
      _x = self.sender
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.destination
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.type
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_i2f.pack(_x.height, _x.abs_cmd_vel_linear_x, _x.abs_cmd_vel_angular_z))
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
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.sender = str[start:end].decode('utf-8')
      else:
        self.sender = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.destination = str[start:end].decode('utf-8')
      else:
        self.destination = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.type = str[start:end].decode('utf-8')
      else:
        self.type = str[start:end]
      _x = self
      start = end
      end += 12
      (_x.height, _x.abs_cmd_vel_linear_x, _x.abs_cmd_vel_angular_z,) = _struct_i2f.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_i2f = struct.Struct("<i2f")
