# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from stdr_msgs/ThermalSourceVector.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import stdr_msgs.msg
import geometry_msgs.msg

class ThermalSourceVector(genpy.Message):
  _md5sum = "dddbbf1cf2eb1ad9e8f6f398fb8b44ac"
  _type = "stdr_msgs/ThermalSourceVector"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# Thermal sources list
stdr_msgs/ThermalSource[] thermal_sources

================================================================================
MSG: stdr_msgs/ThermalSource
# Source description

string id
float32 degrees

# sensor pose, relative to the map origin
geometry_msgs/Pose2D pose 

================================================================================
MSG: geometry_msgs/Pose2D
# This expresses a position and orientation on a 2D manifold.

float64 x
float64 y
float64 theta"""
  __slots__ = ['thermal_sources']
  _slot_types = ['stdr_msgs/ThermalSource[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       thermal_sources

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(ThermalSourceVector, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.thermal_sources is None:
        self.thermal_sources = []
    else:
      self.thermal_sources = []

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
      length = len(self.thermal_sources)
      buff.write(_struct_I.pack(length))
      for val1 in self.thermal_sources:
        _x = val1.id
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        if python3:
          buff.write(struct.pack('<I%sB'%length, length, *_x))
        else:
          buff.write(struct.pack('<I%ss'%length, length, _x))
        buff.write(_struct_f.pack(val1.degrees))
        _v1 = val1.pose
        _x = _v1
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.theta))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.thermal_sources is None:
        self.thermal_sources = None
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.thermal_sources = []
      for i in range(0, length):
        val1 = stdr_msgs.msg.ThermalSource()
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.id = str[start:end].decode('utf-8')
        else:
          val1.id = str[start:end]
        start = end
        end += 4
        (val1.degrees,) = _struct_f.unpack(str[start:end])
        _v2 = val1.pose
        _x = _v2
        start = end
        end += 24
        (_x.x, _x.y, _x.theta,) = _struct_3d.unpack(str[start:end])
        self.thermal_sources.append(val1)
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
      length = len(self.thermal_sources)
      buff.write(_struct_I.pack(length))
      for val1 in self.thermal_sources:
        _x = val1.id
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        if python3:
          buff.write(struct.pack('<I%sB'%length, length, *_x))
        else:
          buff.write(struct.pack('<I%ss'%length, length, _x))
        buff.write(_struct_f.pack(val1.degrees))
        _v3 = val1.pose
        _x = _v3
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.theta))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.thermal_sources is None:
        self.thermal_sources = None
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.thermal_sources = []
      for i in range(0, length):
        val1 = stdr_msgs.msg.ThermalSource()
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.id = str[start:end].decode('utf-8')
        else:
          val1.id = str[start:end]
        start = end
        end += 4
        (val1.degrees,) = _struct_f.unpack(str[start:end])
        _v4 = val1.pose
        _x = _v4
        start = end
        end += 24
        (_x.x, _x.y, _x.theta,) = _struct_3d.unpack(str[start:end])
        self.thermal_sources.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_3d = struct.Struct("<3d")
_struct_f = struct.Struct("<f")
