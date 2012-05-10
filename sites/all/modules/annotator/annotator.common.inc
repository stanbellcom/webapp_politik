<?php
  //globals
  $GLOBALS['IP_ADDRESS'] = '192.168.1.102';
  $GLOBALS['PORT_NR'] = '5000';

function annotator_get_notes_by_attachment_id($bilag_id){
  global $user;
  $url = $GLOBALS['IP_ADDRESS'].':'.$GLOBALS['PORT_NR'].'/search?drupal_user='.$user->name.'&bilag_id='.$bilag_id;
  
  return annotator_get_results($url);
}

function annotator_get_notes_by_bullet_point_id($bullet_point_id){
  global $user;
  $url = $GLOBALS['IP_ADDRESS'].':'.$GLOBALS['PORT_NR'].'/search?drupal_user='.$user->name.'&bullet_point_id='.$bullet_point_id;
  
  return annotator_get_results($url);
}

function annotator_get_notes_by_meeting_id($meeting_id){
  global $user;
  $url = $GLOBALS['IP_ADDRESS'].':'.$GLOBALS['PORT_NR'].'/search?drupal_user='.$user->name.'&meeting_id='.$meeting_id;

  return annotator_get_results($url);
}

function annotator_get_results($url){
  $ch = curl_init();

  // Set query data here with the URL
  curl_setopt($ch, CURLOPT_URL, $url); 

  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_TIMEOUT, '1');
  $content_json = trim(curl_exec($ch));
  curl_close($ch);
  
  $content = json_decode($content_json, true);
  return $content['rows'];
}
?>
