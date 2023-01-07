/*
* Chris Forte
* 12/06/2022
* COMPSCI 657
* "bin.cs" File
*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bin : MonoBehaviour
{
    public GameObject top_bun;
    public GameObject bottom_bun;
    public GameObject burger;
    public GameObject cheese_1;
    public GameObject cheese_2;
    public GameObject cheese_3;
    public GameObject lettuce;
    public GameObject onion;
    public GameObject pickles;
    public GameObject tomato;

    public GameObject refridgerator;
    public GameObject grill;
    public GameObject storage_counter;
    public GameObject trash;
    public GameObject pickup_counter;
    public GameObject prep_counter;
    public GameObject floor;

    public Collider c_refridgerator;
    public Collider c_grill;
    public Collider c_storage_counter;
    public Collider c_trash;
    public Collider c_pickup_counter;
    public Collider c_prep_counter;
    public Collider c_floor;

    Vector3 fridge_bin = new Vector3(-12.0863f,102.5f,-352.6201f);
    Vector3 storage_bin = new Vector3(-712f,52.2f,-404.1302f);

    public List<GameObject> refridgerator_list = new List<GameObject>();
    public List<GameObject> storage_list = new List<GameObject>(); 

    void Start() {

        if (refridgerator != null) {
            c_refridgerator = refridgerator.GetComponent<Collider>();
        }

        if (grill != null) {
            c_grill = grill.GetComponent<Collider>();
        }

        if (storage_counter != null) {
            c_storage_counter = storage_counter.GetComponent<Collider>();
        }

        if (trash != null) {
            c_trash = trash.GetComponent<Collider>();
        }

        if (pickup_counter != null) {
            c_pickup_counter = pickup_counter.GetComponent<Collider>();
        }

        if (prep_counter != null) {
            c_prep_counter = prep_counter.GetComponent<Collider>();
        }

        if (floor != null) {
            c_floor = floor.GetComponent<Collider>();
        }

        refridgerator_list.Add(cheese_1);
        refridgerator_list.Add(cheese_2);
        refridgerator_list.Add(cheese_3);
        refridgerator_list.Add(lettuce);
        refridgerator_list.Add(onion);
        refridgerator_list.Add(pickles);
        refridgerator_list.Add(tomato);
        refridgerator_list.Add(burger);

        storage_list.Add(top_bun);
        storage_list.Add(bottom_bun);
    }

    void FoodNumFridge() {
        print(refridgerator_list.Count);
    }

    void FoodNumStorage() {
        print(storage_list.Count);
    }

    void OnTriggerEnter(Collider other) {
        if (bottom_bun.GetComponent<Collider>().bounds.Intersects(c_floor.bounds)) {
            Debug.Log("Bottom Bun Has Been Dropped! Grab a New One!");
        }

        if (top_bun.GetComponent<Collider>().bounds.Intersects(c_floor.bounds)) {
            Debug.Log("Top Bun Has Been Dropped! Grab a New One!");
        }

        if (burger.GetComponent<Collider>().bounds.Intersects(c_floor.bounds)) {
            Debug.Log("Burger Has Been Dropped! Grab a New One!");
        }

        if (cheese_1.GetComponent<Collider>().bounds.Intersects(c_floor.bounds)) {
            Debug.Log("Cheese (Cheddar) Has Been Dropped! Grab a New One!");
        }

        if (cheese_2.GetComponent<Collider>().bounds.Intersects(c_floor.bounds)) {
            Debug.Log("Cheese (Sharp Cheddar) Has Been Dropped! Grab a New One!");
        }

        if (cheese_3.GetComponent<Collider>().bounds.Intersects(c_floor.bounds)) {
            Debug.Log("Cheese (Extra Sharp Cheddar) Has Been Dropped! Grab a New One!");
        }

        if (lettuce.GetComponent<Collider>().bounds.Intersects(c_floor.bounds)) {
            Debug.Log("Lettuce Has Been Dropped! Grab a New One!");
        }

        if (onion.GetComponent<Collider>().bounds.Intersects(c_floor.bounds)) {
            Debug.Log("Onion Has Been Dropped! Grab a New One!");
        }
        
        if (pickles.GetComponent<Collider>().bounds.Intersects(c_floor.bounds)) {
            Debug.Log("Pickles Have Been Dropped! Grab a New One!");
        }

        if (tomato.GetComponent<Collider>().bounds.Intersects(c_floor.bounds)) {
            Debug.Log("Tomato Has Been Dropped! Grab a New One!");
        }

        if (bottom_bun.GetComponent<Collider>().bounds.Intersects(c_prep_counter.bounds)) {
            Debug.Log("Order is Being Prepared!");
        }

        if (burger.GetComponent<Collider>().bounds.Intersects(c_grill.bounds)) {
            Debug.Log("Burger is Cooking");
        }

    }
}
