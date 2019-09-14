/**
 * Importacion de las dependencias
*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/hugetlb.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>

/**
 * Estructuras
*/
struct task_struct *task;
struct task_struct *task_child;
struct list_head *list;

/**
 * Definiciones
*/
#define PROCESZ "cpu_201513700"
#define BUFSIZE 100

/**
 * Informacion sobre el modulo que estamos construyendo
*/
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modulo para obtener informacion del estado de los proceso del cpu.");
MODULE_AUTHOR("ChristianReal-201513700");
/**
 * Fin descripcion del modulo
*/

/**
 * ESCRIBIR ARCHIVO
*/
static int mostrar_informacion_show(struct seq_file *m, void *v) {
        seq_printf(m, "+---------------------------+\n");
        seq_printf(m, "+--------- MODULO CPU ------+\n");
        seq_printf(m, "+---------------------------+\n");
        seq_printf(m, "| 201513700\n");
        seq_printf(m, "| Christian Real\n");
        seq_printf(m, "| Debian 9 Stretch\n");
  
    for_each_process( task ){            
		seq_printf(m, "\n| Pid: %d Nombre: %s Estado: %ld",task->pid, task->comm, task->state); 
		list_for_each(list, &task->children){                        
		    task_child = list_entry( list, struct task_struct, sibling );     
		    seq_printf(m, "\n| Pid: %d Nombre: %s Estado: %ld", 
		    task_child->pid, task_child->comm, task_child->state);
		}   
	} 

        seq_printf(m, "+---------------------------\n");
        return 0;
}

static int hello_proc_open(struct inode *inode, struct  file *file) {
  return single_open(file, mostrar_informacion_show, NULL);
}

static struct file_operations myops =
{
        .owner = THIS_MODULE,
        .open = hello_proc_open,
        .read = seq_read,
        .llseek = seq_lseek,
        .release = single_release,
};
/**
 * FIN ESCRITURA ARCHIVO
*/

static int procedimiento_inicial(void)
{
    proc_create(PROCESZ,0,NULL,&myops);
    printk(KERN_INFO "Christian Adolfo Real Ixcayau\n");
    return 0;
}
 
static void procedimiento_final(void)
{
  remove_proc_entry(PROCESZ,NULL);
  printk(KERN_INFO "Sistemas Operativos 1 [Segundo Semestre 2019]\n");
}
 
module_init(procedimiento_inicial);
module_exit(procedimiento_final); 