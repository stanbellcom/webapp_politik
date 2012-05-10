<?php
function check_user_can_see_bullet_point($meeting_id, $bullet_point_id){
    global $user;
    if (!$user->uid)
      return false;
    if (check_bullet_point_is_part_of_meeting($meeting_id, $bullet_point_id)){
      $bullet_points = entity_load('node', array($bullet_point_id), array('type'=>'bullet_point'));
      $is_closed = $bullet_points[$bullet_point_id]->field_bul_point_closed['und'][0]['value'];

      if (intval($is_closed) == 0){ //is opened
	return true;
      } else { //is closed
	$user_ent = entity_load('user', array($user->uid));

	$meetings = entity_load('node', array($meeting_id), array('type'=>'meeting'));
	$meeting_committee_id = $meetings[$meeting_id]->field_committee['und'][0]['tid'];

	if (!empty($user_ent[$user->uid]->field_user_committee)){  
	  foreach ($user_ent[$user->uid]->field_user_committee['und'] as $user_committee_id){  
	    if (intval($meeting_committee_id) == $user_committee_id['tid']){
	      return true;
	    }
	  }
	}
	//none of the above, access denied
	return false;
      }
    } else 
      return false;
}

function check_user_can_see_bullet_point_attachment($meeting_id, $bullet_point_id, $bullet_point_attachment_id){
  if (check_attachment_is_part_of_bullet_point($bullet_point_id, $bullet_point_attachment_id))
    return check_user_can_see_bullet_point($meeting_id, $bullet_point_id);
  else
    return false;
}


function check_bullet_point_is_part_of_meeting($meeting_id, $bullet_point_id){
    $meetings = entity_load('node', array($meeting_id), array('type'=>'meeting'));
    $meeting = $meetings[$meeting_id];
    
    $contains = false;
    if (!empty($meeting->field_ref_bullet_points['und'])){
      foreach ($meeting->field_ref_bullet_points['und'] as $ref_bullet_point){
	if (intval($bullet_point_id) == intval($ref_bullet_point['target_id'])){	
	  $contains = true;
	  break;
	}
      }
    }
    return $contains;
}

function check_attachment_is_part_of_bullet_point($bullet_point_id, $bilag_id){
    $bullet_points = entity_load('node', array($bullet_point_id), array('type'=>'bullet_point'));
    $bullet_point = $bullet_points[$bullet_point_id];

    $contains = false;
    if (!empty($bullet_point->field_ref_attachment['und'])){
      foreach ($bullet_point->field_ref_attachment['und'] as $ref_bullet_point_attachment){
	if (intval($bilag_id) == intval($ref_bullet_point_attachment['target_id'])){	
	  $contains = true;
	  break;
	}
      }
    }
    return $contains;
}
?>
