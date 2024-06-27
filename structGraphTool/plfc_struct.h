struct bus_type {
    const char        *name;
    const char        *dev_name;
    struct device        *dev_root;
    const struct attribute_group **bus_groups;
    const struct attribute_group **dev_groups;
    const struct attribute_group **drv_groups;

    int (*match)(struct device *dev, struct device_driver *drv);
    int (*uevent)(struct device *dev, struct kobj_uevent_env *env);
    int (*probe)(struct device *dev);
    int (*remove)(struct device *dev);
    void (*shutdown)(struct device *dev);

    int (*online)(struct device *dev);
    int (*offline)(struct device *dev);

    int (*suspend)(struct device *dev, pm_message_t state);
    int (*resume)(struct device *dev);

    int (*num_vf)(struct device *dev);

    int (*dma_configure)(struct device *dev);

    const struct dev_pm_ops *pm;

    const struct iommu_ops *iommu_ops;

    struct subsys_private *p;
    struct lock_class_key lock_key;

    bool need_parent_lock;
};

struct pci_driver {
    struct list_head    node;
    const char        *name;
    const struct pci_device_id *id_table;    /* Must be non-NULL for probe to be called */
    int  (*probe)(struct pci_dev *dev, const struct pci_device_id *id);    /* New device inserted */
    void (*remove)(struct pci_dev *dev);    /* Device removed (NULL if not a hot-plug capable driver) */
    int  (*suspend)(struct pci_dev *dev, pm_message_t state);    /* Device suspended */
    int  (*suspend_late)(struct pci_dev *dev, pm_message_t state);
    int  (*resume_early)(struct pci_dev *dev);
    int  (*resume) (struct pci_dev *dev);    /* Device woken up */
    void (*shutdown) (struct pci_dev *dev);
    int  (*sriov_configure) (struct pci_dev *dev, int num_vfs); /* On PF */
    const struct pci_error_handlers *err_handler;
    const struct attribute_group **groups;
    struct device_driver    driver;
    struct pci_dynids    dynids;
};

struct device_driver {
    const char        *name;
    struct bus_type        *bus;

    struct module        *owner;
    const char        *mod_name;    /* used for built-in modules */

    bool suppress_bind_attrs;    /* disables bind/unbind via sysfs */
    enum probe_type probe_type;

    const struct of_device_id    *of_match_table;
    const struct acpi_device_id    *acpi_match_table;

    int (*probe) (struct device *dev);
    int (*remove) (struct device *dev);
    void (*shutdown) (struct device *dev);
    int (*suspend) (struct device *dev, pm_message_t state);
    int (*resume) (struct device *dev);
    const struct attribute_group **groups;

    const struct dev_pm_ops *pm;
    void (*coredump) (struct device *dev);

    struct driver_private *p;
};

struct driver_private {
    struct kobject kobj;
    struct klist klist_devices;
    struct klist_node knode_bus;
    struct module_kobject *mkobj;
    struct device_driver *driver;
};

struct kobject {
    const char        *name;
    struct list_head    entry;
    struct kobject        *parent;
    struct kset        *kset;
    struct kobj_type    *ktype;
    struct kernfs_node    *sd; /* sysfs directory entry */
    struct kref        kref;
#ifdef CONFIG_DEBUG_KOBJECT_RELEASE
    struct delayed_work    release;
#endif
    unsigned int state_initialized:1;
    unsigned int state_in_sysfs:1;
    unsigned int state_add_uevent_sent:1;
    unsigned int state_remove_uevent_sent:1;
    unsigned int uevent_suppress:1;
};

struct subsys_private {
    struct kset subsys;
    struct kset *devices_kset;
    struct list_head interfaces;
    struct mutex mutex;

    struct kset *drivers_kset;
    struct klist klist_devices;
    struct klist klist_drivers;
    struct blocking_notifier_head bus_notifier;
    unsigned int drivers_autoprobe:1;
    struct bus_type *bus;

    struct kset glue_dirs;
    struct class *class;
};
struct kset {
    struct list_head list;
    spinlock_t list_lock;
    struct kobject kobj;
    const struct kset_uevent_ops *uevent_ops;
};

struct kobj_type {
    void (*release)(struct kobject *kobj);
    const struct sysfs_ops *sysfs_ops;
    struct attribute **default_attrs;
    const struct kobj_ns_type_operations *(*child_ns_type)(struct kobject *kobj);
    const void *(*namespace)(struct kobject *kobj);
};

struct sysfs_ops {
    ssize_t    (*show)(struct kobject *, struct attribute *, char *);
    ssize_t    (*store)(struct kobject *, struct attribute *, const char *, size_t);
};
struct dev_pm_ops {
    int (*prepare)(struct device *dev);
    void (*complete)(struct device *dev);
    int (*suspend)(struct device *dev);
    int (*resume)(struct device *dev);
    int (*freeze)(struct device *dev);
    int (*thaw)(struct device *dev);
    int (*poweroff)(struct device *dev);
    int (*restore)(struct device *dev);
    int (*suspend_late)(struct device *dev);
};

struct kset_uevent_ops {
    int (* const filter)(xxxxxxx);
    const char *(* const name)(struct kset *kset, struct kobject *kobj);
    int (* const uevent)(struct kset *kset, struct kobject *kobj, struct kobj_uevent_env *env);
};

struct qla_init_msix_entry {
    const char *name;
    irq_handler_t handler;
};

struct attribute_group {
    const char        *name;
    umode_t            (*is_visible)(struct kobject *, struct attribute *, int);
    umode_t            (*is_bin_visible)(struct kobject *,struct bin_attribute *, int);
    struct attribute    **attrs;
    struct bin_attribute    **bin_attrs;
};

struct bus_attribute {
    struct attribute    attr;
    ssize_t (*show)(struct bus_type *bus, char *buf);
    ssize_t (*store)(struct bus_type *bus, const char *buf, size_t count);
};

struct klist {
    spinlock_t        k_lock;
    struct list_head    k_list;
    void            (*get)(struct klist_node *);
    void            (*put)(struct klist_node *);
} ;

struct pci_device_id {
    __u32 vendor_device;        /* Vendor and device ID or PCI_ANY_ID*/
    __u32 subvendor_subdevice;    /* Subsystem ID's or PCI_ANY_ID */
    __u32 class_class_mask;    /* (class,subclass,prog-if) triplet */
    kernel_ulong_t driver_data;    /* Data private to the driver */
};

struct device {
    struct device        *parent;

    struct device_private    *p;

    struct kobject kobj;
    const char        *init_name; /* initial name of the device */
    const struct device_type *type;

    struct mutex        mutex;    /* mutex to synchronize calls to
                     * its driver.
                     */

    struct bus_type    *bus;        /* type of bus device is on */
    struct device_driver *driver;    /* which driver has allocated this
                       device */
    void        *platform_data;    /* Platform specific data, device
                       core doesn't touch it */
    void        *driver_data;    /* Driver data, set and get with
                       dev_set/get_drvdata */
    struct dev_links_info    links;
    const struct attribute_group **groups;    /* optional groups */
    void    (*release)(struct device *dev);
    struct iommu_group    *iommu_group;
    struct iommu_fwspec    *iommu_fwspec;
};

struct dev_links_info {
    struct list_head suppliers;
    struct list_head consumers;
    enum dl_dev_state status;
};

struct pci_dynids {
    spinlock_t        lock;    /* Protects list, index */
    struct list_head    list;    /* For IDs added at runtime */
};

///////////////////////////////////
struct  qla2xxx_pci_driver {
    struct pci_driver  pci_driver;
};

struct   pci_bus_type {
    struct bus_type  bus_type;
};

struct  driver_ktype {
    struct kobj_type kobj_type;
};

struct  driver_sysfs_ops  {
   struct sysfs_ops sysfs_ops;
};
 struct  qla2xxx_pci_tbl{
     struct pci_device_id pci_device_id;
 };
struct  bus_kset  {
   struct kset kset;
};
struct  bus_uevent_ops  {
   struct kset_uevent_ops kset_uevent_ops;
};