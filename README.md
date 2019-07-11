An asynchronous IO library which is the easiest to use for cpp. Inspired by Future and Tokio of Rust community.


#### Progress
- [ ] future
    - [x] Context
    - [x] Future
    - [x] Stream
    - [ ] common multi-thread runtime
        - [ ] load balancing
        - [ ] work stealing
        - [x] block_on
        - [ ] spawn
    - [ ] utils
        - [ ] mutex
        - [ ] rwlock
        - [ ] channel
- [x] generator (stackful, segmented stack, based on boost::coroutine2)
    - [x] Generator
- [x] coroutine (based on generator)
    - [x] async
        - [x] async closure
        - [x] async function
    - [x] await
        - [x] await Future
        - [x] await Stream
- [ ] sio (core io runtime, based on libuv and uvw)
    - [ ] multi-thread runtime
        - [ ] specialize common multi-thread runtime
    - [ ] asynchronous io implementation
        - [ ] network
            - [ ] TCP
            - [ ] UDP
            - [ ] DNS
            - [ ] network interfaces
        - [ ] file system
            - [ ] normal operations
                - [ ] open
                - [ ] close
                - [ ] read   
                - [ ] write
                - [ ] unlink
                - [ ] makedir
                - [ ] mkdtemp
                - [ ] rmdir
                - [ ] scandir
                - [ ] scandir_next
                - [ ] stat
                - [ ] fstat
                - [ ] rename
                - [ ] fsync
                - [ ] fdatasync
                - [ ] truncate
                - [ ] sendfile
                - [ ] access
                - [ ] chmod
                - [ ] utime
                - [ ] futime
                - [ ] lstat
                - [ ] link
            - [ ] buffer and stream
                - [ ] pipe_init
                - [ ] pipe_open
                - [ ] read_start
                - [ ] read_stop
            - [ ] file change events 
                - [ ] event_init
                - [ ] event_start
            - [ ] custom events 

        
        
    