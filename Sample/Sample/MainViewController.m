//
//  MainViewController.m
//  Sample
//
//  Created by Gil on 2/18/14.
//  Copyright (c) 2014 ValuePotion. All rights reserved.
//

#import "MainViewController.h"
#import "ValuePotion.h"

@interface MainViewController ()

@end

@implementation MainViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)cacheInterstitial:(id)sender
{
    [[ValuePotion sharedInstance] cacheInterstitial:@"default"];
}

- (IBAction)showInterstitial:(id)sender
{
    [[ValuePotion sharedInstance] openInterstitial:@"default"];
}

- (IBAction)sendCustomEvent:(id)sender
{
    // non-purchase event
    NSLog(@"Track non-purchase event.");
    [[ValuePotion sharedInstance] trackEvent:@"test_event1" value:@3];
    
    // purchase event
    NSLog(@"Track purchase event.");
    [[ValuePotion sharedInstance] trackPurchaseEvent:@"item1_purchase" revenueAmount:0.99 currency:@"USD" transactionId:nil productId:nil];
}

@end
