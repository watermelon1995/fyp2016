# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from stdr_msgs/Noise.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class Noise(genpy.Message):
  _md5sum = "a882ac96256e87f019f2655e9d7f0f81"
  _type = "stdr_msgs/Noise"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """bool noise
float32 noiseMean
float32 noiseStd
"""
  __slots__ = ['noise','noiseMean','noiseStd']
  _slot_types = ['bool','float32','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       noise,noiseMean,noiseStd

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Noise, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.noise is None:
        self.noise = False
      if self.noiseMean is None:
        self.noiseMean = 0.
      if self.noiseStd is None:
        self.noiseStd = 0.
    else:
      self.noise = False
      self.noiseMean = 0.
      self.noiseStd = 0.

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
      buff.write(_struct_B2f.pack(_x.noise, _x.noiseMean, _x.noiseStd))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 9
      (_x.noise, _x.noiseMean, _x.noiseStd,) = _struct_B2f.unpack(str[start:end])
      self.noise = bool(self.noise)
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
      buff.write(_struct_B2f.pack(_x.noise, _x.noiseMean, _x.noiseStd))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

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
      end += 9
      (_x.noise, _x.noiseMean, _x.noiseStd,) = _struct_B2f.unpack(str[start:end])
      self.noise = bool(self.noise)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_B2f = struct.Struct("<B2f")
