<?php
	
	function sned($message){
        	$host = "127.0.0.1";
            $port = 12345;

            if( ! ( $client = socket_create( AF_INET, SOCK_STREAM, SOL_TCP ) ) ){
                print "socket_create(): " 	. socket_strerror( socket_last_error( $client ) ) . "\n";
                exit( 1 );
            }
            if( ! socket_connect( $client, $host, $port ) ){
                print "socket_connect(): " 	. socket_strerror( socket_last_error( $client ) ) . "\n";
                exit( 1 );
            }
            socket_write($client, $message, strlen($message));
            
            socket_close( $client );
	}
	
	#===================================================================
	$xml  = file_get_contents('php://input');
	$params = xmlrpc_decode( $xml );
	#-------------------------------------------------------------------
	# $method = $_SERVER[ 'SCRIPT_NAME' ];
	$method = basename( $_SERVER[ 'SCRIPT_FILENAME' ] );
	$method = substr( $method, 0, -4 );
	#-------------------------------------------------------------------
	$array = array( 
		'method' => $method,
		'params' =>	$params[0],
	);
	
	$res = xmlrpc_encode_request(NULL, $array["params"]);
	#-------------------------------------------------------------------
	error_log($array['params']);
	
	sned($array['params']);
	
	print $res;
	#===================================================================
	
?>
