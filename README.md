# preemy

Like preeny( https://github.com/zardus/preeny ), but for Microsoft Windows instead of *nix.

A series of injectable DLLs, and an interface to load them into executables via CreateRemoteThread injection.


##Working features
* Main application can successfully inject a dll whose location is hard-coded in
* send_module sucessfully injects and blocks send()

##Broken features
* rand_module successfully injects, but throws an error for trying to initialize the form in DLLMain