function init(name) {
    jQuery(document).ready(function() {
	jQuery('#content').annotator().annotator('addPlugin', 'Touch', {
	  force: location.search.indexOf('force') > -1,
	  useHighlighter: location.search.indexOf('highlighter') > -1
	});
	//jQuery('#content').annotator().annotator('addPlugin', 'Tags');
	//jQuery('#content').annotator().annotator('addPlugin', 'Filter');
	
	jQuery('#content').annotator().annotator('addPlugin', 'Store', {
	  // The endpoint of the store on your server.
	  prefix: 'http://192.168.42.178:5000/',
	  annotationData: {
             'drupal_user': name
	  },
	  loadFromSearch: {
	     'drupal_user': name
          }
	});
 	
     });

}
