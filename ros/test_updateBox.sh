while true; do
  clear
  rosservice call /stdr_server/updateBox "{}"
  sleep 0.1
done
