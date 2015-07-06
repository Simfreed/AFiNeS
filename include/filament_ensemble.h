/*
 *  filament_ensemble.h
 *  
 *
 *  Authors : Shiladitya Banerjee, Simon Freedman
 *  Copyright 2013 University of Chicago. All rights reserved.
 *
 */

//=====================================
//include guard
#ifndef __FILAMENT_ENSEMBLE_H_INCLUDED__
#define __FILAMENT_ENSEMBLE_H_INCLUDED__

//=====================================
// forward declared dependencies

//=====================================
//included dependences
#include "string"
#include "vector"
#include "map"
#include "filament.h"

//=====================================
//filament network class
template <class filament_type>
class filament_ensemble
{
    public:
        filament_ensemble();

        ~filament_ensemble();
        
        void quad_update_monomer(int i);
        
        void quad_update();

        vector<filament_type *> * get_network();

        map<array<int,2>, double> get_dist(double x, double y);

        map<array<int, 2>, double> update_dist_map(map<array<int,2>, double> t_map, array<int, 2> mquad, double x, double y);
        
        array<double,2> get_direction(int fil, int link);

        array<double,2> get_intpoints(int fil, int link, double xp, double yp);

        array<double,2> get_start(int fil, int link);
        
        array<double,2> get_end(int fil, int link);
        
        array<double,2> get_force(int fil, int actin);
        
        double get_int_direction(int fil, int link, double xp, double yp);

        double get_xcm(int fil, int link);
        
        double get_ycm(int fil, int link);

        double get_angle(int fil, int link);

        double get_llength(int fil, int link);
       
        int get_nactins();
        
        int get_nlinks();

        void update_shear();
        
        void update_stretching();
        
        void update_bending();
        
        void update_int_forces();

        void update_positions(double t);

        void update_forces(int fil, int actin, double f2, double f3);

        void write_actins(ofstream& fout);
        
        void write_links(ofstream& fout);
        
        void write_thermo(ofstream& fout);
        
        void set_straight_filaments(bool is_straight);

        void set_shear_rate(double);

        bool is_polymer_start(int f, int a);

        void set_fov(double x, double y);

        void set_nq(double x, double y);

        void set_ld(double l);

        void set_visc(double v);

        vector<int> get_broken();

        void clear_broken();
        
        void print_filament_thermo();

        void print_network_thermo();

        void update(double t);
        
    protected:

        double dt, temperature, rho, ld, link_ld, visc, gamma, min_time;
        
        int npolymer, nmon;
        
        bool straight_filaments = false;
        
        array<double,2> fov, view;
        array<int, 2> nq;
        vector<int> broken_filaments, empty_vector;
        
        map<array<int, 2>, vector<array<int, 2> > > quad_fils;
        
        vector<filament_type *> network;
};

class ATfilament_ensemble:
    public filament_ensemble<filament>
{

    public:
        
        ATfilament_ensemble(double density, array<double,2> myfov, array<int, 2> mynq, double delta_t, double temp, 
                double len, double vis, int nactin,
                double link_len, vector<array<double, 3> > pos_sets, double stretching, double bending, double frac_force, 
                string bc, double seed);
        
};

class baoab_filament_ensemble:
    public filament_ensemble<baoab_filament>
{
    public:

        baoab_filament_ensemble(double density, array<double,2> myfov, array<int, 2> mynq, double delta_t, double temp, 
                double len, double vis, int nactin,
                double link_len, vector<array<double, 3> > pos_sets, double stretching, double bending, double frac_force, 
                string bc, double seed);

        void update_velocities_B();

        void update_velocities_O(double t);

        void update(double t);

};

class lammps_filament_ensemble:
    public filament_ensemble<lammps_filament>
{
    public:

        lammps_filament_ensemble(double density, array<double,2> myfov, array<int, 2> mynq, double delta_t, double temp, 
                double len, double vis, int nactin,
                double link_len, vector<array<double, 3> > pos_sets, double stretching, double bending, double frac_force, 
                string bc, double seed);

        void set_mass(double m);

        void update_drag();

        void update_brownian();

        void update(double t);
};

class langevin_leapfrog_filament_ensemble:
    public filament_ensemble<langevin_leapfrog_filament>
{
    public:

        langevin_leapfrog_filament_ensemble(double density, array<double,2> myfov, array<int, 2> mynq, double delta_t, double temp, 
                double len, double vis, int nactin,
                double link_len, vector<array<double, 3> > pos_sets, double stretching, double bending, double frac_force, 
                string bc, double seed);

        void set_mass(double m);

        void update_velocities(double t);

        void update_positions(double t);

        void update(double t);
    
};
#endif