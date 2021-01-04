service ClientHelloService {
	oneway void sayHello(1:string msg);
}

service ServerByeService {
	oneway void sayBye(1:string msg);
}