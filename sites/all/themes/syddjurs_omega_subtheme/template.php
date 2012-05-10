<?php

/**
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 *
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
 */
function syddjurs_omega_subtheme_preprocess_page(&$variables) {
    $view = views_get_page_view();
    if (!empty($view)){
      drupal_add_js(drupal_get_path('theme', 'syddjurs_omega_subtheme') .'/js/syddjurs.js');
      if($view->name == 'meeting_details') {
	//adding expand/collapse behaviour
	drupal_add_js('bullet_point_collapse_expand_behaviour()', 'inline');
	$variables['views'] = '';
      } 
      if ($view->name == 'meeting_details' || $view->name == 'speaking_paper'){
	//adding has notes indicator to attachment
	$annotations = annotator_get_notes_by_meeting_id(arg(1));
	$attachment_ids = array();
	foreach ($annotations as $note){
	  $attachment_ids[] = $note['bilag_id'];
	}
	$attachment_ids = array_unique($attachment_ids);
	$attachment_ids = implode(",", $attachment_ids);
	drupal_add_js('ids = ['.$attachment_ids.']; bullet_point_attachment_add_notes_indicator(ids)', 'inline');
      }
    }
}