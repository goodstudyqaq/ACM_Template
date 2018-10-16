//手动扩栈
//主函数写在Main里面即可
//在前面还要宏定义 OPENSTACK
int main()
{
#ifdef OPENSTACK
    int size = 70 << 20; // 256MB
    char *p = (char*)malloc(size) + size;
#if (defined _WIN64) or (defined __unix)
    __asm__("movq %0, %%rsp\n" :: "r"(p));
#else
    __asm__("movl %0, %%esp\n" :: "r"(p));
#endif
#endif
    Main();
#ifdef OPENSTACK
    exit(0);
#else
    return 0;
#endif
}
