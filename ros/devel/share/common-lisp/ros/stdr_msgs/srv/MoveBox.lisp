; Auto-generated. Do not edit!


(cl:in-package stdr_msgs-srv)


;//! \htmlinclude MoveBox-request.msg.html

(cl:defclass <MoveBox-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass MoveBox-request (<MoveBox-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MoveBox-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MoveBox-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name stdr_msgs-srv:<MoveBox-request> is deprecated: use stdr_msgs-srv:MoveBox-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MoveBox-request>) ostream)
  "Serializes a message object of type '<MoveBox-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MoveBox-request>) istream)
  "Deserializes a message object of type '<MoveBox-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MoveBox-request>)))
  "Returns string type for a service object of type '<MoveBox-request>"
  "stdr_msgs/MoveBoxRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveBox-request)))
  "Returns string type for a service object of type 'MoveBox-request"
  "stdr_msgs/MoveBoxRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MoveBox-request>)))
  "Returns md5sum for a message object of type '<MoveBox-request>"
  "d41d8cd98f00b204e9800998ecf8427e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MoveBox-request)))
  "Returns md5sum for a message object of type 'MoveBox-request"
  "d41d8cd98f00b204e9800998ecf8427e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MoveBox-request>)))
  "Returns full string definition for message of type '<MoveBox-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MoveBox-request)))
  "Returns full string definition for message of type 'MoveBox-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MoveBox-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MoveBox-request>))
  "Converts a ROS message object to a list"
  (cl:list 'MoveBox-request
))
;//! \htmlinclude MoveBox-response.msg.html

(cl:defclass <MoveBox-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass MoveBox-response (<MoveBox-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MoveBox-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MoveBox-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name stdr_msgs-srv:<MoveBox-response> is deprecated: use stdr_msgs-srv:MoveBox-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MoveBox-response>) ostream)
  "Serializes a message object of type '<MoveBox-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MoveBox-response>) istream)
  "Deserializes a message object of type '<MoveBox-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MoveBox-response>)))
  "Returns string type for a service object of type '<MoveBox-response>"
  "stdr_msgs/MoveBoxResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveBox-response)))
  "Returns string type for a service object of type 'MoveBox-response"
  "stdr_msgs/MoveBoxResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MoveBox-response>)))
  "Returns md5sum for a message object of type '<MoveBox-response>"
  "d41d8cd98f00b204e9800998ecf8427e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MoveBox-response)))
  "Returns md5sum for a message object of type 'MoveBox-response"
  "d41d8cd98f00b204e9800998ecf8427e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MoveBox-response>)))
  "Returns full string definition for message of type '<MoveBox-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MoveBox-response)))
  "Returns full string definition for message of type 'MoveBox-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MoveBox-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MoveBox-response>))
  "Converts a ROS message object to a list"
  (cl:list 'MoveBox-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'MoveBox)))
  'MoveBox-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'MoveBox)))
  'MoveBox-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveBox)))
  "Returns string type for a service object of type '<MoveBox>"
  "stdr_msgs/MoveBox")